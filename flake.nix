{
  description = "BrasioEngine — Vulkan renderer dev shell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };

        buildInputs = with pkgs; [
          libGL
          libGLU
          glew
          glfw
          glm

          vulkan-headers
          vulkan-loader
          vulkan-validation-layers
          vulkan-tools

          yaml-cpp

          libx11
          libxrandr
          libxi
          libxcursor
          libxinerama
          libxxf86vm
        ];

        nativeBuildInputs = with pkgs; [
          bear
          cmake
          ninja
          pkg-config
          shaderc
        ];
      in
      {
        devShells.default = pkgs.mkShell {
          inherit buildInputs nativeBuildInputs;

          hardeningDisable = [ "fortify" ];

          VK_LAYER_PATH = "${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d";

          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
            pkgs.vulkan-loader
            pkgs.libGL
          ];
        };
      });
}
