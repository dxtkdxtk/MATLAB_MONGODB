% connectdb;
IF1min = GetBar('IF1409', 1, today - 1, today - 1);
IF3min = GetBar('IF1409', 3, today - 1, today - 1);
IF5min = GetBar('IF1409', 5, today - 1, today - 1);
IF15min = GetBar('IF1409', 15, today - 1, today - 1);
IF30min = GetBar('IF1409', 30, today - 1, today - 1);
IF60min = GetBar('IF1409', 60, today - 1, today - 1);
IFday = GetBar('IF1409', 1440, today - 1, today - 1);
BarTime2MatlabTime(IF1min);