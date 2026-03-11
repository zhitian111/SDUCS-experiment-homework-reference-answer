#!/usr/bin/env fish

# Define ANSI color codes
set ESC "\033"
set RED "{$ESC}[91m"
set GREEN "{$ESC}[92m"
set YELLOW "{$ESC}[93m"
set BLUE "{$ESC}[94m"
set RESET "{$ESC}[0m"

# Check for Python and Node.js
if not command -v python >/dev/null 2>&1
    echo -e "[{$YELLOW}WARNING{$RESET}] Python not found, startup may fail."
end
if not command -v node >/dev/null 2>&1
    echo -e "[{$YELLOW}WARNING{$RESET}] Node.js not found, npx/npm startup may fail."
end

set port 8000

echo -e "[{$YELLOW}NOTICE{$RESET}] After successful startup, visit http://127.0.0.1:$port/ to view the result. You can modify the script to change the listening port."
sleep 1
echo -e "[{$BLUE}INFO{$RESET}] Attempting to start server with Python..."
sleep 1
python -m http.server $port --bind 127.0.0.1; or begin
    echo -e "[{$RED}ERROR{$RESET}] Startup failed. Please check network connection, port availability, or Python configuration."
    sleep 1
    echo -e "[{$BLUE}INFO{$RESET}] Attempting to start server with npx..."
    sleep 1
    npx http-server -p $port -a 127.0.0.1; or begin
        echo -e "[{$RED}ERROR{$RESET}] Startup failed. Please check network connection, port availability, or npx configuration."
        sleep 1
        echo -e "[{$BLUE}INFO{$RESET}] Attempting to start server with npm..."
        sleep 1
        npm run serve; or begin
            echo -e "[{$RED}ERROR{$RESET}] Startup failed. Please check network connection, port availability, or Node.js environment and modules."
            sleep 1
            echo -e "[{$RED}ERROR{$RESET}] All startup methods failed. Please check network connection, environment configuration, run the script with elevated privileges, start the server manually, or use another method to view the page."
            sleep 1
        end
    end
end

exit 0