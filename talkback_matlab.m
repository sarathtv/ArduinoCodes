%GET a TalkBack Command using m file
% TalkBack app ID
TalkBack_ID = '45273';
% TalkBack command ID
Command_ID = '27613534';
% TalkBack app API key
TalkBack_apikey = 'DS4YLUANDDQ0HC9E';
url = strcat('https://api.thingspeak.com/talkbacks/',TalkBack_ID,'/commands/',Command_ID,'.json');
data = webread(url,'api_key',TalkBack_apikey)
