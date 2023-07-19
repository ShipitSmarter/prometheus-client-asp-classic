<%

' A registry of Collectors
' Responsible for collecting all the metrics when Prometheus scrapes.
Class prom_CollectorRegistry
    Private m_list_collectors

    Private m_prefix
    Public Property Let Prefix(value)
        m_prefix = value
    End Property
    Public Property Get Prefix
        prefix = m_prefix
    End Property

    Private Sub Class_Initialize()
        Set m_list_collectors = prom_new_arraylist
    End Sub

    Public Sub register(collector)
        m_list_collectors.Add(collector)
    End Sub

    Public Sub unregister(collector)
        m_list_collectors.Remove(collector)
    End Sub

    Public Sub clear()
        m_list_collectors.Clear()
    End Sub

    ' Get MetricFamilySamples from all registered Collectors
    Public Function gather()
        Dim i, metric_families()
        ReDim metric_families(m_list_collectors.Count - 1)

        For i = 0 To UBound(metric_families)
            Set metric_families(i) = m_list_collectors(i).collect()
        Next
        gather = metric_families
    End Function
End Class

%>