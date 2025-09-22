@echo off
setlocal enabledelayedexpansion

REM 设置输出文件
set "output_file=output.md"

REM 清空或创建输出文件
> "%output_file%" echo # C++ 文件列表

REM 遍历所有.cpp文件
for /r %%f in (*.cpp) do (
    set "filename=%%~nf"
    set "filepath=%%~f"
    
    REM 将文件名写入输出文件
    echo. >> "%output_file%"
    echo # %%~nxf - %%~dpf >> "%output_file%"
    
    REM 将代码块写入输出文件
    echo ```cpp >> "%output_file%"
    type "%%f" >> "%output_file%"
    echo ``` >> "%output_file%"
)

echo 处理完成！输出已保存到 %output_file%
endlocal