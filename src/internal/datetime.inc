<%

' Get the current datetime according to the system and convert it to UTC timezone
Public Function getCurrentDateTimeUtc()
    Dim datetime
    Set dateTime = CreateObject("WbemScripting.SWbemDateTime")    
    dateTime.SetVarDate (now())
    getCurrentDateTimeUtc = dateTime.GetVarDate (false)
End Function

' Returns the Unix epoch for the provided datetime string
Public Function convertUtcDateTimeToEpoch(strDateTime)
    convertUtcDateTimeToEpoch = dateDiff("s", "01/01/1970 00:00:00", strDateTime)
End Function

%>