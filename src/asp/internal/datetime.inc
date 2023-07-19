<%

' Get the current datetime according to the system and convert it to UTC timezone
Public Function prom_get_current_datetime_utc()
    Dim datetime
    Set dateTime = CreateObject("WbemScripting.SWbemDateTime")    
    dateTime.SetVarDate (now())
    prom_get_current_datetime_utc = dateTime.GetVarDate (false)
End Function

' Returns the Unix epoch for the provided datetime string
Public Function prom_convert_datetime_utc_to_epoch(str_datetime)
    prom_convert_datetime_utc_to_epoch = dateDiff("s", "01/01/1970 00:00:00", str_datetime)
End Function

%>