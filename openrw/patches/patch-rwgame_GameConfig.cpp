$NetBSD$

--- rwgame/GameConfig.cpp.orig	2016-08-12 00:03:52.000000000 +0000
+++ rwgame/GameConfig.cpp
@@ -43,7 +43,7 @@ bool GameConfig::isValid()
 
 std::string GameConfig::getDefaultConfigPath()
 {
-#if defined(RW_LINUX) || defined(RW_FREEBSD) || defined(RW_OPENBSD)
+#if defined(RW_LINUX) || defined(RW_FREEBSD) || defined(RW_NETBSD) || defined(RW_OPENBSD)
 	char* config_home = getenv("XDG_CONFIG_HOME");
 	if (config_home != nullptr) {
 		return std::string(config_home) + "/" + kConfigDirectoryName;
@@ -93,4 +93,3 @@ int GameConfig::handler(void* user,
 
 #undef MATCH
 }
-
