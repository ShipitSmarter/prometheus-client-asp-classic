<%

' Class to combine an Array key and Object value (not supported in Dictionary).
Class prom_KeyValuePair
    Private m_key
    Public Property Get Key
        Key = m_key
    End Property

    Private m_value
    Public Property Get Value
        Set Value = m_value
    End Property

    Public Function Init(key, obj_value)
        m_key = key
        Set m_value = obj_value
        Set Init = me
    End Function
End Class

%>