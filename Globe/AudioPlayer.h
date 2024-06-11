#pragma once
#include<QAudioOutput>
#include<QMediaPlayer>
#include<QThread>
#include"../Globe/Enum.h"
#include"../Globe/Map.h"
namespace Globe {
	class AudioPlayer
	{
	public:
		class AudioPlayerThread :public QThread {
		public:
			AudioPlayerThread(AudioType audio)
			{
			player->setAudioOutput(audioOutput);
			QUrl url(Map::AudioMap[audio]);
			player->setSource(url);
			};
			void run()override
			{
				player->play();
				connect(player, &QMediaPlayer::mediaStatusChanged, this, 
					[this](QMediaPlayer::MediaStatus status) {
					if (status == QMediaPlayer::EndOfMedia || status == QMediaPlayer::InvalidMedia) {
						delete player;
						delete audioOutput;
						this->quit(); // 请求线程退出  
					}
					});
				exec(); // 进入事件循环，等待信号和槽的处理  
			}
		private:
			 QMediaPlayer* player{ new QMediaPlayer{} };
			 QAudioOutput* audioOutput{ new QAudioOutput{}};
		};

		static void Play(AudioType audio);
	};
}