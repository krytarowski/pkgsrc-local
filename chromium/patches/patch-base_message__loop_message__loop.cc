$NetBSD$

--- base/message_loop/message_loop.cc.orig	2016-06-16 19:02:01.000000000 +0000
+++ base/message_loop/message_loop.cc
@@ -222,7 +222,7 @@ std::unique_ptr<MessagePump> MessageLoop
 // TODO(abarth): Figure out if we need this.
 #define MESSAGE_PUMP_UI std::unique_ptr<MessagePump>()
 #else
-#define MESSAGE_PUMP_UI std::unique_ptr<MessagePump>(new MessagePumpForUI())
+#define MESSAGE_PUMP_UI 0 // std::unique_ptr<MessagePump>(new MessagePumpForUI())
 #endif
 
 #if defined(OS_MACOSX)
