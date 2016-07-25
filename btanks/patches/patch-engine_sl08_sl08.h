$NetBSD$

--- engine/sl08/sl08.h.orig	2016-07-25 01:00:24.395460943 +0000
+++ engine/sl08/sl08.h
@@ -272,7 +272,7 @@ namespace sl08 {
 			inline slot1(object_type *object, func_t func, signal_type * signal = NULL) : object(object), func(func) {}
 
 			inline void assign(object_type *o, func_t f) { object = o; func = f; }
-			inline void assign(object_type *o, func_t f, signal_type &signal_ref = NULL) { object = o; func = f; connect(signal_ref); }
+			inline void assign(object_type *o, func_t f, signal_type &signal_ref = NULL) { object = o; func = f; this->connect(signal_ref); }
 	
 			inline return_type operator() (arg1_type a1) const { 
 				return (object->*func) (a1) ;
@@ -293,7 +293,7 @@ namespace sl08 {
 			inline slot1 () : object(NULL), func(NULL) {}
 			inline slot1 (object_type *object, func_t func) : object(object), func(func) {}
 			inline void assign(object_type *o, func_t f) { object = o; func = f; }
-			inline void assign(object_type *o, func_t f, signal_type &signal_ref) { object = o; func = f; connect(signal_ref); }
+			inline void assign(object_type *o, func_t f, signal_type &signal_ref) { object = o; func = f; this->connect(signal_ref); }
 	
 			inline void operator() (arg1_type a1) const { 
 				(object->*func) (a1); 
@@ -447,7 +447,7 @@ namespace sl08 {
 			inline slot2(object_type *object, func_t func, signal_type * signal = NULL) : object(object), func(func) {}
 
 			inline void assign(object_type *o, func_t f) { object = o; func = f; }
-			inline void assign(object_type *o, func_t f, signal_type &signal_ref = NULL) { object = o; func = f; connect(signal_ref); }
+			inline void assign(object_type *o, func_t f, signal_type &signal_ref = NULL) { object = o; func = f; this->connect(signal_ref); }
 	
 			inline return_type operator() (arg1_type a1, arg2_type a2) const { 
 				return (object->*func) (a1, a2) ;
@@ -468,7 +468,7 @@ namespace sl08 {
 			inline slot2 () : object(NULL), func(NULL) {}
 			inline slot2 (object_type *object, func_t func) : object(object), func(func) {}
 			inline void assign(object_type *o, func_t f) { object = o; func = f; }
-			inline void assign(object_type *o, func_t f, signal_type &signal_ref) { object = o; func = f; connect(signal_ref); }
+			inline void assign(object_type *o, func_t f, signal_type &signal_ref) { object = o; func = f; this->connect(signal_ref); }
 	
 			inline void operator() (arg1_type a1, arg2_type a2) const { 
 				(object->*func) (a1, a2); 
@@ -643,7 +643,7 @@ namespace sl08 {
 			inline slot3 () : object(NULL), func(NULL) {}
 			inline slot3 (object_type *object, func_t func) : object(object), func(func) {}
 			inline void assign(object_type *o, func_t f) { object = o; func = f; }
-			inline void assign(object_type *o, func_t f, signal_type &signal_ref) { object = o; func = f; connect(signal_ref); }
+			inline void assign(object_type *o, func_t f, signal_type &signal_ref) { object = o; func = f; this->connect(signal_ref); }
 	
 			inline void operator() (arg1_type a1, arg2_type a2, arg3_type a3) const { 
 				(object->*func) (a1, a2, a3); 
@@ -797,7 +797,7 @@ namespace sl08 {
 			inline slot4(object_type *object, func_t func, signal_type * signal = NULL) : object(object), func(func) {}
 
 			inline void assign(object_type *o, func_t f) { object = o; func = f; }
-			inline void assign(object_type *o, func_t f, signal_type &signal_ref = NULL) { object = o; func = f; connect(signal_ref); }
+			inline void assign(object_type *o, func_t f, signal_type &signal_ref = NULL) { object = o; func = f; this->connect(signal_ref); }
 	
 			inline return_type operator() (arg1_type a1, arg2_type a2, arg3_type a3, arg4_type a4) const { 
 				return (object->*func) (a1, a2, a3, a4) ;
@@ -818,7 +818,7 @@ namespace sl08 {
 			inline slot4 () : object(NULL), func(NULL) {}
 			inline slot4 (object_type *object, func_t func) : object(object), func(func) {}
 			inline void assign(object_type *o, func_t f) { object = o; func = f; }
-			inline void assign(object_type *o, func_t f, signal_type &signal_ref) { object = o; func = f; connect(signal_ref); }
+			inline void assign(object_type *o, func_t f, signal_type &signal_ref) { object = o; func = f; this->connect(signal_ref); }
 	
 			inline void operator() (arg1_type a1, arg2_type a2, arg3_type a3, arg4_type a4) const { 
 				(object->*func) (a1, a2, a3, a4); 
@@ -972,7 +972,7 @@ namespace sl08 {
 			inline slot5(object_type *object, func_t func, signal_type * signal = NULL) : object(object), func(func) {}
 
 			inline void assign(object_type *o, func_t f) { object = o; func = f; }
-			inline void assign(object_type *o, func_t f, signal_type &signal_ref = NULL) { object = o; func = f; connect(signal_ref); }
+			inline void assign(object_type *o, func_t f, signal_type &signal_ref = NULL) { object = o; func = f; this->connect(signal_ref); }
 	
 			inline return_type operator() (arg1_type a1, arg2_type a2, arg3_type a3, arg4_type a4, arg5_type a5) const { 
 				return (object->*func) (a1, a2, a3, a4, a5) ;
