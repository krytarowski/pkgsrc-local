$NetBSD$

--- rwengine/src/engine/SaveGame.cpp.orig	2016-08-11 22:19:42.000000000 +0000
+++ rwengine/src/engine/SaveGame.cpp
@@ -539,7 +539,11 @@ bool SaveGame::loadGame(GameState& state
 	auto icv = iconv_open("UTF-8", "UTF-16");
 	char* saveName = (char*)state.basic.saveName;
 
+#if defined(RW_NETBSD)
+	iconv(icv, (const char**)&saveName, &bytes, &outCur, &outSize);
+#else
 	iconv(icv, &saveName, &bytes, &outCur, &outSize);
+#endif
 	strcpy(state.basic.saveName, outBuff);
 
 	BlockDword scriptBlockSize;
@@ -1286,4 +1290,3 @@ std::vector<SaveGameInfo> SaveGame::getA
 
 	return infos;
 }
-
