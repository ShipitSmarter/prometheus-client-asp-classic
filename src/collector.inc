<!-- #include virtual = "/prometheus-client/metric.inc" -->
<!-- #include virtual = "/prometheus-client/internal/array.inc" -->
<!-- #include virtual = "/prometheus-client/internal/keyvaluepair.inc" -->
<!-- #include virtual = "/prometheus-client/internal/list.inc" -->

<%

' Collector for one metric.
' Contains shared logic for Counter and Gauge.
Class Collector
    Public m_name
    Public m_help
    Public m_labelNames
    Public m_children ' ArrayList of KeyValuePair of Array and Object

    Private Sub Class_Initialize()
        Set m_children = NewArrayList
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

    ' Return all metric samples of this collector.
    ' Needs to be implemtend by "extending" collector.
    Public Function collect()
        Err.Raise 5, "Collector.collect", "This method should not be called."
    End Function

    ' Return the child with the given labels, creating it if needed. Nothing if no child found.
    Public Function getForLabels(p_labelValues)
        validateLabelValues(p_labelValues)
        Dim result: Set result = Nothing
        Dim child
        For Each child In m_children
            If arraysAreEqaul(child.Key, p_labelValues) Then
                Set result = child.Value
                Exit For
            End If
        Next
        Set getForLabels = result
    End Function

    ' Add a new child to the collector. Make sure a child with the same label values does not already exists.
    Public Sub addChild(p_child, p_labelValues)
        validateLabelValues(p_labelValues)
        Dim kvp
        Set kvp = New KeyValuePair.Init(p_labelValues, p_child)
        m_children.Add(kvp)
    End Sub

    ' Raise an error if label values are not valid.
    Private Sub validateLabelValues(p_labelValues)
        If UBound(p_labelValues) <> UBound(m_labelNames) Then
            Err.Raise 5, "Collector.validateLabelValues", "The amount of provided label values (" & UBound(p_labelValues) + 1 & ") does not equal the amount of label names (" & UBound(m_labelNames) + 1 & ") set for collector '" & m_name & "'."
        End If
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
    ' Needs to be implemtend by "extending" builder.
    Public Function register(p_registry)
        Err.Raise 5, "CollectorBuilder.register", "This method should not be called."
    End Function
End Class

%>