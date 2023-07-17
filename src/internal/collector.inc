<!-- #include virtual = "/prometheus-client/internal/metric.inc" -->
<!-- #include virtual = "/prometheus-client/internal/array.inc" -->
<!-- #include virtual = "/prometheus-client/internal/keyvaluepair.inc" -->
<!-- #include virtual = "/prometheus-client/internal/list.inc" -->

<%

' Collector for one metric.
' Contains shared logic for Counter and Gauge.
Class prom_Collector
    Public m_name
    Public m_help
    Public m_label_names
    Public m_list_children ' ArrayList of KeyValuePair of Array and Object

    Private Sub Class_Initialize()
        Set m_list_children = prom_new_arraylist
    End Sub

    Public Function Init(builder)
        If builder().m_name & "" = "" Then
            Err.Raise 5, "prom_Collector.Init", "Name cannot be empty."
        End If
        If builder().m_help & "" = "" Then
            Err.Raise 5, "prom_Collector.Init", "Help cannot be empty."
        End If

        m_name = builder().m_name
        m_help = builder().m_help
        m_label_names = builder().m_label_names
        Set Init = me
    End Function

    ' Return all metric samples of this collector.
    ' Needs to be implemtend by "extending" collector.
    Public Function collect()
        Err.Raise 5, "prom_Collector.collect", "This method should not be called."
    End Function

    ' Return the child with the given labels, creating it if needed. Nothing if no child found.
    Public Function get_for_labels(label_values)
        validate_label_values(label_values)
        Dim result: Set result = Nothing
        Dim child
        For Each child In m_list_children
            If prom_arrays_are_eqaul(child.key, label_values) Then
                Set result = child.value
                Exit For
            End If
        Next
        Set get_for_labels = result
    End Function

    ' Add a new child to the collector. Make sure a child with the same label values does not already exists.
    Public Sub add_child(child, label_values)
        validate_label_values(label_values)
        Dim kvp
        Set kvp = New prom_KeyValuePair.Init(label_values, child)
        m_list_children.add(kvp)
    End Sub

    ' Raise an error if label values are not valid.
    Private Sub validate_label_values(label_values)
        If UBound(label_values) <> UBound(m_label_names) Then
            Err.Raise 5, "prom_Collector.validate_label_values", "The amount of provided label values (" & UBound(label_values) + 1 & ") does not equal the amount of label names (" & UBound(m_label_names) + 1 & ") set for collector '" & m_name & "'."
        End If
    End Sub
End Class

' Builder pattern for creating a prom_Collector
' Contains shared logic for CounterBuilder and GaugeBuilder.
Class prom_CollectorBuilder
    Public m_name
    Public m_help
    Public m_label_names

    Private Sub Class_Initialize()
        m_label_names = Array()
    End Sub

    ' Set the name of the metric. Required.
    Public Function with_name(name)
        m_name = name
        Set with_name = me
    End Function

    ' Set the help string of the metric. Required.
    Public Function with_help(help)
        m_help = help
        Set with_help = me
    End Function

    ' Set the label names of the metric. Optional, defaults to no labels.
    Public Function with_label_names(label_names)
        m_label_names = label_names
        Set with_label_names = me
    End Function

    ' Create and register the collector with the given registry.
    ' Needs to be implemtend by "extending" builder.
    Public Function register(registry)
        Err.Raise 5, "prom_CollectorBuilder.register", "This method should not be called."
    End Function
End Class

%>