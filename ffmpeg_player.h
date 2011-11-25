#ifndef __FFMPEG_PLAYER_H
#define __FFMPEG_PLAYER_H

#include <stdint.h>

#include <agar/core.h>
#include <agar/gui.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ffmpeg.h>

typedef struct ffmpeg_player {
	struct ag_widget _inherit;	/* Inherit from AG_Widget */

	int w, h;			/* user-requested geometry */
	int flags;

	SDL_Surface *screen;
	AG_Surface *surface;
	int surface_id;

	SDL_ffmpegFile *file;
	SDL_ffmpegVideoFrame *frame;

#define FFMPEGPLAYER_BUFSIZE 10
	SDL_ffmpegAudioFrame *audioFrame[FFMPEGPLAYER_BUFSIZE];
	AG_Thread audio_fillThread;
	AG_Cond audio_cond;

	int playing;
	/* syncing */
	uint64_t sync, offset;
} ffmpegPlayer;

__BEGIN_DECLS

extern AG_WidgetClass ffmpegPlayerClass;

ffmpegPlayer *ffmpegPlayerNew(void *parent, int w, int h, int flags,
			      SDL_Surface *screen);
int ffmpegPlayerLoad(ffmpegPlayer *me, const char *path);

enum ffmpegPlayerAction {
	FFMPEGPLAYER_PLAY,
	FFMPEGPLAYER_PAUSE,
	FFMPEGPLAYER_TOGGLE,
	FFMPEGPLAYER_GETPAUSE
};
int ffmpegPlayerAction(ffmpegPlayer *me, enum ffmpegPlayerAction action);

__END_DECLS

#endif