<!-- #include virtual = "/prometheus-client/internal/list.inc" -->

<%

' A registry of Collectors
' Responsible for collecting all the metrics when Prometheus scrapes.
Class CollectorRegistry
    Private m_collectors

    Private m_prefix
    Public Property Let Prefix(p_prefix)
        m_prefix = p_prefix
    End Property
    Public Property Get Prefix
        Prefix = m_prefix
    End Property

    Private Sub Class_Initialize()
        Set m_collectors = NewArrayList
    End Sub

    Public Sub register(p_collector)
        m_collectors.Add(p_collector)
    End Sub

    Public Sub unregister(p_collector)
        m_collectors.Remove(p_collector)
    End Sub

    Public Sub clear()
        m_collectors.Clear()
    End Sub

    ' Get MetricFamilySamples from all registered Collectors
    Public Function gather()
        Dim i, metricFamilies()
        ReDim metricFamilies(m_collectors.Count - 1)

        For i = 0 To UBound(metricFamilies)
            Set metricFamilies(i) = m_collectors(i).collect()
        Next
        gather = metricFamilies
    End Function
End Class

%>