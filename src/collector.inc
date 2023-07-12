<!-- #include virtual = "/prometheus-client/internal/list.inc" -->

<%

' Collector for one metric.
' Contains shared logic for Counter and Gauge.
Class Collector
    Public m_name
    Public m_help
    Public m_labelNames
    Public m_samples

    Private Sub Class_Initialize()
        Set m_samples = NewArrayList
    End Sub

    Public Function Init(p_builder)
        If p_builder().m_name & "" = "" Then
            Err.Raise 5, "Collector.Init", "Name cannot be empty."
        End If
        If p_builder().m_help & "" = "" Then
            Err.Raise 5, "Collector.Init", "Help cannot be empty."
        End If

        m_name = p_builder().m_name
        m_help = p_builder().m_help
        m_labelNames = p_builder().m_labelNames
        Set Init = me
    End Function

    ' Return all metric samples of this collector
    Public Function collect()
        ' TODO
    End Function

    ' Return the sample with the given labels, creating it if needed. Null if no sample found.
    Public Function getByLabels(p_labelValues)
        Dim result: Set result = Nothing
        For Each item in m_samples
            If item.m_labelValues = p_labelValues Then
                Set result = item
                Exit For
            End If
        Next
        Set getByLabels = result
    End Function

    ' Return the single contained sample when no labels are set. Null if no sample found.
    Public Function getWithoutLabels()
        If UBound(m_labelNames) > 0 Then
            Err.Raise 5, "Collector.noLabels", "There are labels set for this metric, use Collector.labels instead."
        End If

        If m_samples.Count = 0 Then
            Set getWithoutLabels = Nothing
        Else
            Set getWithoutLabels = m_samples(0)
        End If
    End Function

    ' Add a new sample to the collector. Make sure a sample with the same label values does not already exists.
    Public Sub addSample(p_sample)
        If UBound(p_sample().m_labelValues) <> UBound(m_labelNames) Then
            Err.Raise 5, "Collector.addSample", "The amount of label values does not correspond with the amount of label names."
        End If
        m_samples.Add(p_sample)
    End Sub
End Class

' Builder pattern for creating a Collector
' Contains shared logic for CounterBuilder and GaugeBuilder.
Class CollectorBuilder
    Public m_name
    Public m_help
    Public m_labelNames

    Private Sub Class_Initialize()
        m_labelNames = Array()
    End Sub

    ' Set the name of the metric. Required.
    Public Function withName(p_name)
        m_name = p_name
        Set withName = me
    End Function

    ' Set the help string of the metric. Required.
    Public Function withHelp(p_help)
        m_help = p_help
        Set withHelp = me
    End Function

    ' Set the label names of the metric. Optional, defaults to no labels.
    Public Function withLabelNames(p_labelNames)
        m_labelNames = p_labelNames
        Set withLabelNames = me
    End Function

    ' Create and register the collector with the given registry.
    ' Needs to be implemtend by "extending" collector.
    Public Function register(p_registry)
        Err.Raise 5, "CollectorBuilder.register", "This method should not be called."
    End Function
End Class

' Shared functionality for the different metric samples
Class Sample
    Public m_labelValues

    Private Sub Class_Initialize()
        m_labelValues = Array()
    End Sub
End Class

%>