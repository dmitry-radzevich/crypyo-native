from conan.tools.files import copy
import os


def deploy(graph, output_folder, **kwargs):
    rootfile = graph.root.conanfile
    multi = rootfile.settings.get_safe("compiler") == "msvc"
    bindir = os.path.join(output_folder, "build", "bin")
    if multi:
        bindir = os.path.join(bindir, str(rootfile.settings.build_type))

    for name, dep in graph.root.conanfile.dependencies.items():
        if dep.folders is None:
            rootfile.output.warning(f"BINDEP: skipping dependency {dep}")
            continue
        srcdirs = [os.path.join(str(dep.folders.package_folder), "bin")]
        srcdirs += dep.cpp_info.libdirs
        
        for srcdir in srcdirs:
            rootfile.output.trace(f"BINDEP: {srcdir} -> {bindir}")
            copy(rootfile, "*.so", srcdir, bindir, False)
            copy(rootfile, "*.dll", srcdir, bindir, False)
            copy(rootfile, "*.dylib", srcdir, bindir, False)
