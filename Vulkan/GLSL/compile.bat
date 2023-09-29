@echo off
for /R %%i in (*.vert, *.frag) do (
    glslangValidator.exe -H -g --hlsl-offsets "%%i" -o "%%~dpi%%~ni%%~xi.spv"
)
echo Done
pause
    