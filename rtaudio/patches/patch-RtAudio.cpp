$NetBSD$

--- RtAudio.cpp.orig	2016-02-22 21:15:53.000000000 +0000
+++ RtAudio.cpp
@@ -8682,10 +8682,12 @@ RtAudio::DeviceInfo RtApiOss :: getDevic
   // Probe channels
   if ( ainfo.caps & PCM_CAP_OUTPUT ) info.outputChannels = ainfo.max_channels;
   if ( ainfo.caps & PCM_CAP_INPUT ) info.inputChannels = ainfo.max_channels;
+#ifdef PCM_CAP_DUPLEX
   if ( ainfo.caps & PCM_CAP_DUPLEX ) {
     if ( info.outputChannels > 0 && info.inputChannels > 0 && ainfo.caps & PCM_CAP_DUPLEX )
       info.duplexChannels = (info.outputChannels > info.inputChannels) ? info.inputChannels : info.outputChannels;
   }
+#endif
 
   // Probe data formats ... do for input
   unsigned long mask = ainfo.iformats;
@@ -8695,8 +8697,10 @@ RtAudio::DeviceInfo RtApiOss :: getDevic
     info.nativeFormats |= RTAUDIO_SINT8;
   if ( mask & AFMT_S32_LE || mask & AFMT_S32_BE )
     info.nativeFormats |= RTAUDIO_SINT32;
+#ifdef AFMT_FLOAT
   if ( mask & AFMT_FLOAT )
     info.nativeFormats |= RTAUDIO_FLOAT32;
+#endif
   if ( mask & AFMT_S24_LE || mask & AFMT_S24_BE )
     info.nativeFormats |= RTAUDIO_SINT24;
 
@@ -10226,4 +10230,3 @@ void RtApi :: byteSwapBuffer( char *buff
   // End:
   //
   // vim: et sts=2 sw=2
-
