@echo off
chcp 65001 >nul
setlocal EnableExtensions

set "PROXY=http://127.0.0.1:7897"
set "HTTP_PROXY=%PROXY%"
set "HTTPS_PROXY=%PROXY%"
set "http_proxy=%PROXY%"
set "https_proxy=%PROXY%"
set "NO_PROXY=localhost,127.0.0.1,::1"
set "no_proxy=%NO_PROXY%"

set "NLP_PROXY=%PROXY%"
set "NLP_HF_HOME=F:\Downloads\huggingface"
set "HF_HOME=%NLP_HF_HOME%"
set "HF_HUB_CACHE=%HF_HOME%\hub"
set "TRANSFORMERS_CACHE=%HF_HUB_CACHE%"
set "HUGGINGFACE_HUB_CACHE=%HF_HUB_CACHE%"
set "NLP_TMP=%HF_HOME%\_tmp"
set "TMP=%NLP_TMP%"
set "TEMP=%TMP%"
set "TMPDIR=%TMP%"
if not exist "%TMP%" mkdir "%TMP%" 2>nul
if not exist "%HF_HUB_CACHE%" mkdir "%HF_HUB_CACHE%" 2>nul

set "HF_HUB_DISABLE_XET=1"
set "HF_HUB_DISABLE_SYMLINKS_WARNING=1"
set "HF_HUB_DOWNLOAD_TIMEOUT=1200"

set "HERE=%~dp0"
set "HERE=%HERE:~0,-1%"
set "VENV_PY=%HERE%\..\.venv\Scripts\python.exe"

if not exist "%VENV_PY%" (
  echo [错误] 未找到虚拟环境: %VENV_PY%
  pause
  exit /b 1
)

set "ARG=%~1"
if "%ARG%"=="" set "ARG=21"
if /i "%ARG%"=="20" goto RUN20
if /i "%ARG%"=="21" goto RUN21
if /i "%ARG%"=="all" goto RUNALL

echo 用法: %~nx0 [20^|21^|all]
pause
exit /b 2

:RUN20
pushd "%HERE%"
"%VENV_PY%" "%HERE%\实验二十-智能问答基础实验——基于大语言模型的.py"
set "ERR=%ERRORLEVEL%"
popd
pause
exit /b %ERR%

:RUN21
pushd "%HERE%"
"%VENV_PY%" "%HERE%\实验二十一-文本摘要生成实验——基于预训练语言.py"
set "ERR=%ERRORLEVEL%"
popd
pause
exit /b %ERR%

:RUNALL
call "%~f0" 20
set "E1=%ERRORLEVEL%"
call "%~f0" 21
set "E2=%ERRORLEVEL%"
if not "%E1%"=="0" exit /b %E1%
exit /b %E2%
