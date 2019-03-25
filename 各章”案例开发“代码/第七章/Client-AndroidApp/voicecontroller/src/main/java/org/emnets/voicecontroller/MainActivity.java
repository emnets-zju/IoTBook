package org.emnets.voicecontroller;

import android.media.MediaPlayer;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import java.io.File;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    private Button btnRecord = null;
    private boolean isRecording = false;
    private AudioRecorder audioRecorder = null;
    private MediaPlayer mediaPlayer = null;
    private File fileAudio = null;
    public String TAG = "AudioController";
    private AudioSender audioSender = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnRecord = (Button) findViewById(R.id.btnRecord);
        btnRecord.setOnLongClickListener(new startRecordAudio());
        btnRecord.setOnClickListener(new stopRecordAudio());

    }

    public class startRecordAudio implements View.OnLongClickListener {

        @Override
        public boolean onLongClick(View view) {
            isRecording = true;
            audioRecorder = new AudioRecorder();
            new Thread(new Runnable() {
                @Override
                public void run() {
                    fileAudio = audioRecorder.startRecord();
                }
            }).start();
            return false;   //false说明结束后调用短按动作，true说明不调用
        }
    }

    public class stopRecordAudio implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            if (isRecording) {
                Log.e(TAG,"录音结束");
                audioRecorder.stopRecord();
                isRecording = false;
            }

            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                Log.e(TAG,"等待出错");
            }
            Log.e(TAG, fileAudio.getAbsolutePath());
            mediaPlayer = new MediaPlayer();
            try{
                mediaPlayer.setDataSource(fileAudio.getAbsolutePath());
                mediaPlayer.prepare();
                mediaPlayer.start();
            }catch(IOException e){
                Log.e(TAG,"播放失败");
            }

            //将音频文件传输到云端
            audioSender = new AudioSender(fileAudio.getAbsolutePath());
            audioSender.start();
        }
    }
}
