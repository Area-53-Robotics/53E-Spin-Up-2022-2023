{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs = { self, nixpkgs }:
    let 
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
    pythonPackages = pkgs.python310Packages;
    
    in
    {
      devShell.x86_64-linux = pkgs.mkShell {
        buildInputs = [ 
        pkgs.virtualenv
        pythonPackages.wheel
        pythonPackages.pip
        pkgs.gcc-arm-embedded
        pkgs.clang-tools
        ];
      };
    };
}
