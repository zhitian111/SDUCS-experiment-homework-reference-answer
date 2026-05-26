@echo off
chcp 65001 >nul
setlocal EnableExtensions

REM -----------------------------------------------------------------------------
REM 环境与作用范围说明（不写注册表、不改「系统环境变量」）
REM   - 本脚本里的 set 只作用于当前这个 cmd 窗口，以及由它启动的子进程（pip、python）。
REM   - 未使用 setx，不会把代理写入用户级或机器级环境变量。
REM   - 已 setlocal：若你在「同一个 cmd」里用 call 本脚本，脚本结束后会恢复调用前的环境。
REM   - 双击运行时单独弹窗，关窗后其中的 HTTP_PROXY 等不会残留到系统或其它软件。
REM   - pip 安装的包仍写入你的 .venv（这是预期行为）。
REM -----------------------------------------------------------------------------

REM =============================================================================
REM 第七周实验十三：代理 + 依赖安装
REM   配置代理并安装NER依赖.bat                 默认：仅 PyTorch 路线（transformers，无 TensorFlow）
REM   配置代理并安装NER依赖.bat install         同上
REM   配置代理并安装NER依赖.bat install-hanlp   安装 hanlp[full]（体积大，含 tensorflow）
REM   配置代理并安装NER依赖.bat run             仅设置代理并运行「实验十三」
REM   配置代理并安装NER依赖.bat all             先「默认安装」再运行实验十三
REM
REM 若 pip 报错 OSError 28 No space left on device：通常是 C 盘临时目录、pip 缓存或 HF 缓存盘满。
REM   可在下方「磁盘空间」一节取消注释并改成你空间足够的目录（例如 F 盘）。
REM 默认代理 http://127.0.0.1:7897，请按你的软件修改 PROXY。
REM =============================================================================

REM ------------- 磁盘空间（按需取消注释并修改路径）-------------
REM set "TMP=F:\Homework\_tmp"
REM set "TEMP=%TMP%"
REM set "TMPDIR=%TMP%"
REM set "PIP_CACHE_DIR=F:\Homework\_pip_cache"
REM set "HF_HOME=F:\Homework\_hf_cache"
REM if not exist "%TMP%" mkdir "%TMP%" 2>nul
REM if not exist "%PIP_CACHE_DIR%" mkdir "%PIP_CACHE_DIR%" 2>nul
REM if not exist "%HF_HOME%" mkdir "%HF_HOME%" 2>nul
REM -------------------------------------------------------------

set "PROXY=http://127.0.0.1:7897"
set "HTTP_PROXY=%PROXY%"
set "HTTPS_PROXY=%PROXY%"
set "http_proxy=%PROXY%"
set "https_proxy=%PROXY%"
set "NO_PROXY=localhost,127.0.0.1,::1"
set "no_proxy=%NO_PROXY%"
REM 避免 Hub 走 XET 路径在部分网络下长时间无进度（与实验十三脚本默认一致）
set "HF_HUB_DISABLE_XET=1"
REM 国内镜像示例（按需取消注释）
REM set "HF_ENDPOINT=https://hf-mirror.com"
REM Hugging Face 访问令牌（勿把真实 token 提交到 git；仅本 cmd 窗口有效）
REM set "HF_TOKEN=hf_你的令牌"

set "HERE=%~dp0"
set "HERE=%HERE:~0,-1%"
set "NLP_ROOT=%HERE%\.."
set "VENV_PY=%NLP_ROOT%\.venv\Scripts\python.exe"

if not exist "%VENV_PY%" (
  echo [错误] 未找到虚拟环境:
  echo   %VENV_PY%
  echo 请在「自然语言处理作业」目录下创建 .venv 后重试。
  pause
  exit /b 1
)

set "ARG=%~1"
if "%ARG%"=="" set "ARG=install"

if /i "%ARG%"=="run" goto RUN_ONLY
if /i "%ARG%"=="install" goto DO_INSTALL_PYTORCH
if /i "%ARG%"=="install-hanlp" goto DO_INSTALL_HANLP
if /i "%ARG%"=="all" goto DO_INSTALL_PYTORCH

echo [错误] 未知参数: %~1
echo 请使用 install、install-hanlp、run 或 all
pause
exit /b 2

:DO_INSTALL_PYTORCH
echo [信息] Python: "%VENV_PY%"
echo [信息] 代理: %HTTPS_PROXY%
echo [信息] 模式: PyTorch 路线（transformers，无需 hanlp[full]）
echo.

"%VENV_PY%" -m pip install -U pip setuptools wheel
if errorlevel 1 goto PIP_FAIL

echo.
echo [步骤] 安装 transformers 相关（若本机已有 torch，通常无需再下载巨型 torch 包）...
"%VENV_PY%" -m pip install -U transformers huggingface_hub accelerate safetensors
if errorlevel 1 goto PIP_FAIL

echo.
echo [完成] PyTorch 路线依赖已就绪。若本机尚未安装 torch，请另行: pip install torch
if /i "%ARG%"=="all" (
  echo [信息] 接着运行实验十三...
  goto RUN_CORE
)
echo 可选: 需要 HanLP 完整版时再执行: "%~f0" install-hanlp
echo 运行实验: "%~f0" run
pause
exit /b 0

:DO_INSTALL_HANLP
echo [信息] Python: "%VENV_PY%"
echo [信息] 代理: %HTTPS_PROXY%
echo [信息] 模式: hanlp[full]（含 tensorflow，体积大）
echo.

"%VENV_PY%" -m pip install -U pip setuptools wheel
if errorlevel 1 goto PIP_FAIL

echo.
echo [步骤] 安装 hanlp[full]（请耐心等待）...
"%VENV_PY%" -m pip install -U "hanlp[full]"
if errorlevel 1 goto PIP_FAIL

echo.
echo [步骤] 升级 transformers、huggingface_hub...
"%VENV_PY%" -m pip install -U transformers huggingface_hub accelerate
if errorlevel 1 goto PIP_FAIL

echo.
echo [完成] HanLP 完整依赖已安装。
pause
exit /b 0

:RUN_ONLY
echo [信息] 仅运行实验十三（使用代理环境变量，便于 HuggingFace 下载）
echo [信息] Python: "%VENV_PY%"
echo [信息] 代理: %HTTPS_PROXY%
echo.

:RUN_CORE
pushd "%HERE%"
echo [信息] 工作目录: %CD%
"%VENV_PY%" "%HERE%\实验十三-命名实体识别实验——信息抽取基础.py"
set "ERR=%ERRORLEVEL%"
popd
if not "%ERR%"=="0" (
  echo.
  echo [提示] PyTorch 路线需 torch、transformers 与可下载模型的网络或代理。
  echo [提示] 若 HanLP 提示缺少 tensorflow，请执行: "%~f0" install-hanlp
  echo [提示] 若 OSError 28，请编辑本 bat 打开「磁盘空间」一节的 TEMP、PIP_CACHE_DIR、HF_HOME。
)
pause
exit /b %ERR%

:PIP_FAIL
echo.
echo [错误] pip 失败。请检查: 代理与端口；磁盘空间（Errno 28 时修改 TEMP、PIP_CACHE_DIR、HF_HOME）；Python 与 tensorflow 是否兼容（仅 install-hanlp 时）。
pause
exit /b 1
