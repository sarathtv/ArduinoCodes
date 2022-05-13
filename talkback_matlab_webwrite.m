%Use webwrite with TalkBack
%Write a TalkBack Command
% TalkBack app ID
TALKBACK_ID = '45273'; 
% TalkBack command ID
Command_ID = '27613534'; 
% TalkBack app API key
TALKBACK_APIKEY = 'DS4YLUANDDQ0HC9E'; 
url =  strcat('https://api.thingspeak.com/talkbacks/',TALKBACK_ID,'/commands.json');
response = webwrite(url,'api_key',TALKBACK_APIKEY,'command_string','CLOSEDOOR')