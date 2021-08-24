#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <thread>
#include <string.h>
#include <gst/gst.h>
#include <glib.h>

using std::vector;
using namespace std;

        int songIndex = 3;
        GMainLoop *loop;

        vector<char *> songFile()
        {
            DIR *dir;
            struct dirent *diread;
            vector<char *> files;
            if((dir = opendir("/home/pooja/Songs"))!=nullptr)
            {
                while((diread = readdir(dir))!=nullptr){
                    files.push_back(diread->d_name);
                }
                closedir(dir);
            }else {
                perror("opendir");
                // return EXIT_FAILURE;
            }
            return files;
        };

        string returnCurrentSongNumber(int songCount)
        {
            vector<char *> storeSongs = songFile();
            return storeSongs[songCount];
        };

        vector<char *> gstfiles = songFile();

        int songList()
        {
            vector<char *> songsTemp = songFile();

            int i = 1;
            for(auto file : songsTemp) 
            {
                cout << i << "." << file << endl;
                i++;
                // cout << endl;
            }

            return songsTemp.size();
        };

        int main(int argc, char *argv[])
        {

        char command;
        GstState state = GST_STATE_PLAYING;

        g_print("CHECK1");

        GstElement *pipeline;

        g_print("CHECK2");

        gst_init(&argc, &argv);

        loop = g_main_loop_new (NULL, FALSE);

        g_print("CHECK3");

        //
        // int userInput = songIndex;
        vector<char *> gstfiles = songFile();
        string filepath = "filesrc location=/home/pooja/Songs/";
        char cmd_str[100];
        strcpy(cmd_str, filepath.c_str());
        strcat(cmd_str, gstfiles[songIndex]);
        strcat(cmd_str, " ! mpegaudioparse ! avdec_mp3 ! audioconvert ! audioresample ! pulsesink");
        g_print(gstfiles[songIndex]);
        g_print(cmd_str);
        //
        // cout << gstfiles[songIndex] << endl;

        // pipeline = gst_parse_launch(" filesrc location=/home/pooja/Songs/Alone.mp3 ! mpegaudioparse ! avdec_mp3 ! audioconvert ! audioresample ! pulsesink" , NULL);

        pipeline = gst_parse_launch(cmd_str , NULL);


        g_print("CHECK4");

        gst_element_set_state(pipeline, GST_STATE_PLAYING);

        g_print("CHECK5");

        g_print ("Running...\n");

        // thread t1(g_main_loop_run,loop);
        // t1.detach();
        // g_main_loop_run (loop);

        //  /* Out of the main loop, clean up nicely */
        // g_print ("Returned, stopping playback\n");
        // gst_element_set_state (pipeline, GST_STATE_NULL);

        // g_print ("Deleting pipeline\n");
        // gst_object_unref (GST_OBJECT (pipeline));
        // g_main_loop_unref (loop);

        while(1) {

                g_print("CHECK6");

                command = getchar();

                g_print("CHECK7");

                switch (command)
                {
                case 'p':
                        g_print("CHECK8");
                        
                        if(state == GST_STATE_PLAYING){
                                state = GST_STATE_PAUSED;
                        }
                        // else{
                        //         state = GST_STATE_PLAYING;
                        // }

                        g_print("CHECK9");
                        gst_element_set_state(pipeline,state);
                        g_print("CHECK10");
                        break;
                case 'r':
                        g_print("CHECK11");

                        if(state == GST_STATE_PAUSED || state == GST_STATE_PLAYING || state == GST_STATE_NULL){
                                state = GST_STATE_PLAYING;
                        }
                        // else{
                        //         state = GST_STATE_PAUSED;
                        // }

                        g_print("CHECK12");
                        gst_element_set_state(pipeline,state);
                        g_print("CHECK13");
                        break;
                case 's':
                        g_print("CHECK17");
                        gst_element_set_state(pipeline,GST_STATE_NULL);
                        g_print("CHECK20");
                        break;
                case 'q':
                        g_print("CHECK21");
                        gst_object_unref(pipeline);
                        g_print("CHECK22");
                        exit(0);
                        g_print("CHECK23");
                        break;
                case 'n':
                        g_print("CHECK24");
                        gst_element_set_state(pipeline,GST_STATE_NULL);
                        g_print("CHECK25");
                        int userInput = songIndex++;
                        // pipeline = gst_parse_launch(" filesrc location=/home/pooja/Songs/Alone.mp3 ! mpegaudioparse ! avdec_mp3 ! audioconvert ! audioresample ! pulsesink" , NULL);
                        
                        //***************
                        strcpy(cmd_str, filepath.c_str());
                        strcat(cmd_str, gstfiles[userInput]);
                        // g_print(gstfiles[userInput]);
                        cout << "ting" << userInput << endl;
                        g_print(gstfiles[userInput]);
                        strcat(cmd_str, " ! mpegaudioparse ! avdec_mp3 ! audioconvert ! audioresample ! pulsesink");
                        g_print(cmd_str);
                        //***************

                        g_print("CHECK26");
                        pipeline = gst_parse_launch(cmd_str , NULL);
                        g_print("CHECK27");
                        state = GST_STATE_PLAYING;
                        g_print("CHECK28");
                        gst_element_set_state(pipeline, state);
                        g_print("CHECK29");
                        break;

                // case 'n':
                //         if(state == GST_STATE_PLAYING){
                               
                //                 gst_element_set_state (pipeline, GST_STATE_NULL);
                //                 g_main_loop_quit(loop);
                //                 // t1.join();
                //                 // g_print ("Returned, stopping playback\n");
                //                 // gst_element_set_state (pipeline, GST_STATE_NULL);

                //                 // g_print ("Deleting pipeline\n");
                //                 // gst_object_unref (GST_OBJECT (pipeline));
                //                 // g_main_loop_unref (loop);

                //                 loop = g_main_loop_new (NULL, FALSE);

                //                 pipeline = gst_parse_launch("filesrc location=/home/pooja/Songs/Alone.mp3 ! mpegaudioparse ! avdec_mp3 ! audioconvert ! audioresample ! pulsesink" , NULL);
                               
                //                 gst_element_set_state(pipeline, GST_STATE_PLAYING);

                //                 g_print("CHECK5");

                //                 g_print ("Running...\n");

                //                 thread t2(g_main_loop_run,loop);

                //         }
                }
        }

}