<%

' Collector for one metric.
' Contains shared logic for Counter and Gauge.
Class Collector
    Public m_name
    Public m_help
    Public m_labelNames
    Public m_samples

    Public Function Init(p_builder)
        ' TODO
    End Function

    ' Return all metric samples of this collector
    Public Function collect()
        ' TODO
    End Function

    ' Return the sample with the given labels, creating it if needed.
    Public Function labels(p_labelValues)
        ' TODO
    End Function
End Class

' Builder pattern for creating a Collector
' Contains shared logic for CounterBuilder and GaugeBuilder.
Class CollectorBuilder
    Public m_name
    Public m_help
    Public m_labelNames(0)

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

%>