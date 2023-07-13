<%

' Class to combine an Array key and Object value (not supported in Dictionary).
Class KeyValuePair
    Private m_key
    Public Property Get Key
        Key = m_key
    End Property

    Private m_value
    Public Property Get Value
        Set Value = m_value
    End Property

    Public Function Init(p_key, p_value)
        m_key = p_key
        Set m_value = p_value
        Set Init = me
    End Function
End Class

%>