set appName to "OBS"

to startStream()
  activate application "OBS"
  delay 0.5
  tell application "System Events" to tell process "OBS"
	  return click button "Start Streaming" of splitter group 1 of window 1
  end tell
end startStream

if application appName is running then
    return startStream()
else
    tell application "OBS" to launch
    repeat until application "OBS" is running
      delay 0.5
    end repeat
    return startStream()
end if
