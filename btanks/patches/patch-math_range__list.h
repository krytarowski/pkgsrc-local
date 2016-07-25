$NetBSD$

--- math/range_list.h.orig	2008-10-24 14:15:55.000000000 +0000
+++ math/range_list.h
@@ -53,14 +53,14 @@ public: 
 			return;
 		}
 	
-		typename parent_type::iterator i = lower_bound(value);
+		typename parent_type::iterator i = this->lower_bound(value);
 		if (i != parent_type::end()) {
 			if (i->first == value)
 				return;
 
 			if (value + 1 == i->first) {
 				T e = i->second;
-				erase(i);
+				this->erase(i);
 				i = parent_type::insert(typename parent_type::value_type(value, e)).first; //expand beginning
 				i = pack_left(i);
 			}
