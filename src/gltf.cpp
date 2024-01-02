#include "gltf.h"
#include "misc.h"

gltf::TinyGLTF loader = gltf::TinyGLTF();

gltf::Model LoadBasic(string name) {
  gltf::Model model;
  string err, warn;
  bool ret;
  if (name.substr(name.find('.')) == ".glb") {
    ret = loader.LoadBinaryFromFile(&model, &err, &warn, "models/" + name);
  } else {
    ret = loader.LoadASCIIFromFile(&model, &err, &warn, "models/" + name);
  }
  if (!err.empty()) error(err.c_str());
  if (!warn.empty()) error(warn.c_str());
  if (!ret) error("failed to load gltf file");
  return model;
}