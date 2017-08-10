$NetBSD$

--- lib/Support/Triple.cpp.orig	2017-08-10 16:47:06.917844400 +0000
+++ lib/Support/Triple.cpp
@@ -65,6 +65,7 @@ StringRef Triple::getArchTypeName(ArchTy
   case spir64:         return "spir64";
   case kalimba:        return "kalimba";
   case lanai:          return "lanai";
+  case vax:            return "vax";
   case shave:          return "shave";
   case wasm32:         return "wasm32";
   case wasm64:         return "wasm64";
@@ -137,6 +138,7 @@ StringRef Triple::getArchTypePrefix(Arch
   case spir64:      return "spir";
   case kalimba:     return "kalimba";
   case lanai:       return "lanai";
+  case vax:         return "vax";
   case shave:       return "shave";
   case wasm32:
   case wasm64:      return "wasm";
@@ -298,6 +300,7 @@ Triple::ArchType Triple::getArchTypeForL
     .Case("spir64", spir64)
     .Case("kalimba", kalimba)
     .Case("lanai", lanai)
+    .Case("vax", vax)
     .Case("shave", shave)
     .Case("wasm32", wasm32)
     .Case("wasm64", wasm64)
@@ -420,6 +423,7 @@ static Triple::ArchType parseArch(String
     .Case("spir64", Triple::spir64)
     .StartsWith("kalimba", Triple::kalimba)
     .Case("lanai", Triple::lanai)
+    .Case("vax", Triple::vax)
     .Case("shave", Triple::shave)
     .Case("wasm32", Triple::wasm32)
     .Case("wasm64", Triple::wasm64)
@@ -627,6 +631,7 @@ static Triple::ObjectFormatType getDefau
   case Triple::bpfel:
   case Triple::hexagon:
   case Triple::lanai:
+  case Triple::vax:
   case Triple::hsail:
   case Triple::hsail64:
   case Triple::kalimba:
@@ -1195,6 +1200,7 @@ static unsigned getArchPointerBitWidth(l
   case llvm::Triple::spir:
   case llvm::Triple::kalimba:
   case llvm::Triple::lanai:
+  case llvm::Triple::vax:
   case llvm::Triple::shave:
   case llvm::Triple::wasm32:
   case llvm::Triple::renderscript32:
@@ -1275,6 +1281,7 @@ Triple Triple::get32BitArchVariant() con
   case Triple::x86:
   case Triple::xcore:
   case Triple::lanai:
+  case Triple::vax:
   case Triple::shave:
   case Triple::wasm32:
   case Triple::renderscript32:
@@ -1308,6 +1315,7 @@ Triple Triple::get64BitArchVariant() con
   case Triple::hexagon:
   case Triple::kalimba:
   case Triple::lanai:
+  case Triple::vax:
   case Triple::msp430:
   case Triple::nios2:
   case Triple::r600:
@@ -1395,6 +1403,7 @@ Triple Triple::getBigEndianArchVariant()
   case Triple::x86:
   case Triple::x86_64:
   case Triple::xcore:
+  case Triple::vax:
   case Triple::renderscript32:
   case Triple::renderscript64:
 
@@ -1486,6 +1495,7 @@ bool Triple::isLittleEndian() const {
   case Triple::x86_64:
   case Triple::xcore:
   case Triple::tcele:
+  case Triple::vax:
   case Triple::renderscript32:
   case Triple::renderscript64:
     return true;
