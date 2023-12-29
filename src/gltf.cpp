#include "gltf.h"
#include "misc.h"

gltf::TinyGLTF loader{};

gltf::Model LoadModel(string file_name) {
  gltf::Model model;
  string err, warn;
  if (file_name.substr(file_name.find('.')) == ".glb") {
    loader.LoadBinaryFromFile(&model, &err, &warn, file_name);
  } else {
    loader.LoadASCIIFromFile(&model, &err, &warn, file_name);
  }
  if (!err.empty()) error(err.c_str());
  if (!warn.empty()) error(warn.c_str());
  return model;
}