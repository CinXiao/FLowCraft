#include "AudioPlayer.h"

namespace Globe {
	void AudioPlayer::Play(AudioType audio)
	{
		if (RuningConfig::AudioAllowPlay)
		{
			AudioPlayerThread* playerThread = new AudioPlayerThread(audio);
			playerThread->start();
		}
	}
}