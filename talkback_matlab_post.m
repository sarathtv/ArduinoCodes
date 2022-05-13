%POST a TalkBack Command via m file
TALKBACK_ID = '45273';
% TalkBack command ID
Command_ID = '27613534';
% TalkBack app API key
TalkBack_apikey = 'DS4YLUANDDQ0HC9E';
url =  strcat('https://api.thingspeak.com/talkbacks/',TALKBACK_ID,'/commands.json');
options = weboptions('RequestMethod','post');
data = webread(url,'api_key',TalkBack_apikey,'command_string','OPENDOOR',options)