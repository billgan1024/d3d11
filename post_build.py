import sys
import shutil
import os
import re

# "Debug" or "Release"
build_type = sys.argv[1] 

def copy_folder(folder):
  shutil.copytree(folder, os.path.join("build", build_type, folder), dirs_exist_ok=True)

def make_folder(folder):
  os.makedirs(os.path.join("build", build_type, folder), exist_ok=True)

copy_folder("models")
copy_folder("textures")
make_folder("shaders")

# for each fbx file in models, convert to gltf
for file in os.listdir("models"):
  if file.endswith(".fbx"):
    os.system("fbx2gltf models/{} -o build/{}/models/{}.gltf".format(file, build_type, file[:-4]))

shader_version = "5_0"

# for each shader entry point among hlsl files in shaders, compile to cso
for file in os.listdir("shaders"):
  if file.endswith(".hlsl"):
    for main in re.compile("[A-Za-z0-9_]+_[vpcg]s").findall(open(os.path.join("shaders", file), "r").read()):
      print(main)
      cmd = "fxc shaders/{} -T {} -E {} -Fo build/{}/shaders/{}.cso".format(file, main[-2:] + "_" + shader_version, main, build_type, main)
      if build_type == "Debug":
        cmd += " -Zi -Od"

      cmd += " -Fc build/{}/shaders/{}.asm".format(build_type, main) 
      os.system(cmd)
