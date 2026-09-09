# Cross platform Image viewer

currently at the early stage and only supports png files;
PRs are welcome;

only requirements are raylib and gnu make;

it already ships with windows raylib dlls in `libs/win/` dir, if you want your own now you know where to put them;



# To-Do
- support wide variety of image extensions 
  currently using raylib, but i think we can do better by using stb directly

- make seperate static / shared builds & handle raylib versioning

- make pure nuklear file browser (perhaps could be a repo on it's own) and remove tinyfiledialog dependency

- make this pure GL to remove raylib dependency via GLAD

- the final task would be to create a shell build script that fetches all dependencies (ps1/sh)


# Linux

Build:
    Run `make -B` to (re)build everything

    Run `RUNME` binary

# Windows

Build:
    Just run `make win -B` to (re)build everything

    Run `RUNME.exe`



