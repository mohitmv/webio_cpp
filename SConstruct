import sys

import SCons.Variables

variables = SCons.Variables.Variables(args=ARGUMENTS);

variables.Add(SCons.Variables.EnumVariable(
            'env',
            'Running Environment',
            'laptop',
            ['laptop', 'ts']));

args = Environment(variables = variables);

prod_checks = " -Wno-unused-function  -Wno-unused-parameter -Wno-unused-local-typedefs -Werror "

gcc_env = dict();
gcc_env["CXX"] = "g++"
gcc_env["CCFLAGS"] = " -fdiagnostics-color=always -Iinclude"
if (args["env"] == "ts"):
  gcc_env["CCFLAGS"] += " --std=c++11";
elif args["env"] == "laptop":
  gcc_env["CCFLAGS"] += " --std=c++14";

env = Environment(**gcc_env);

env['CXXCOMSTR'] = 'Compiling [$SOURCES] > $TARGET'
env['LINKCOMSTR'] = 'Linking [...] > $TARGET'

core_libs_path = ["src/webio"];

def BuildObject(path):
  env.Object("./build-dbg/"+path+".o", path+".cpp");

def BuildProgram(path, objects_path=[]):
  env.Program("./build-dbg/"+path, list(("./build-dbg/" + i + ".o") for i in objects_path));

def BuildCoreLibs():
  for i in core_libs_path:
    BuildObject(i);

def BuildModule(path, dependency=[]):
  BuildCoreLibs();
  for i in dependency+[path]:
    BuildObject(i);
  BuildProgram(path, core_libs_path + dependency + [path]);


if (ARGUMENTS.get("module", None) != None):
  path = ARGUMENTS.get("module").strip();
  if (path[-4:] == ".cpp"):
    path = path[:-4];
  BuildModule(path);

