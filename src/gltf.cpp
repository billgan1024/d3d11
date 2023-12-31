#include "gltf.h"
#include "misc.h"

gltf::TinyGLTF loader{};

gltf::Model LoadModel(string file_name) {
  gltf::Model model;
  string err, warn;
  bool success;
  if (file_name.substr(file_name.find('.')) == ".glb") {
    success = loader.LoadBinaryFromFile(&model, &err, &warn, "models/" + file_name);
  } else {
    success = loader.LoadASCIIFromFile(&model, &err, &warn, "models/" + file_name);
  }
  if (!err.empty()) error(err.c_str());
  if (!warn.empty()) error(warn.c_str());
  if(!success) error("failed to load gltf file");
  return model;
}