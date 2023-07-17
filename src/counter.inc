<!-- #include virtual = "/prometheus-client/internal/collector.inc" -->
<!-- #include virtual = "/prometheus-client/internal/datetime.inc" -->

<%

' Counter metric collector
Class prom_Counter
    Private m_collector

    Public Function Init(builder)
        Set m_collector = New prom_Collector.Init(builder)
        Set Init = me
    End Function

    Public Function get_for_labels(label_values)
        Dim result
        Set result = m_collector.get_for_labels(label_values)
        If result Is Nothing Then
            Set result = new_child(label_values)
        End If

        Set get_for_labels = result
    End Function

    Public Function get_without_labels()
        Set get_without_labels = get_for_labels(Array())
    End Function

    Public Function collect()
        Dim i, fullname, samples()
        ReDim samples(m_collector.m_list_children.Count - 1)
        fullname = m_collector.m_name & "_total"
        For i = 0 To m_collector.m_list_children.Count - 1
            Dim label_values: label_values = m_collector.m_list_children(i).Key
            Dim child: Set child = m_collector.m_list_children(i).Value
            Set samples(i) = New prom_Sample.Init(fullname, m_collector.m_label_names, label_values, child.Value)
        Next
        Set collect = New prom_MetricFamilySamples.Init(prom_MetricType_COUNTER, fullname, m_collector.m_help, samples)
    End Function

    Private Function new_child(labels)
        Dim child
        Set child = New prom_CounterChild
        m_collector.add_child child, labels
        Set new_child = child
    End Function
End Class

' Builder pattern for Counter
Class prom_CounterBuilder
    Private e_collectionBuilder
    Public Default Property Get extended_builder ' Extending CollectorBuilder
        Set extended_builder = e_collectionBuilder
    End Property

    Private Sub Class_Initialize()
        Set e_collectionBuilder = New prom_CollectorBuilder
    End Sub

    ' Create and register the collector with the given registry.
    Public Function register(registry)
        Dim counter
        Set counter = New prom_Counter.Init(me)
        registry.register(counter)
        Set register = counter
    End Function
End Class

' The value of a single Counter.
Class prom_CounterChild
    Private m_dbl_value
    Public Property Get Value
        Value = m_dbl_value
    End Property
    
    ' The datetime when the counter was created, in seconds since epoch
    Private m_created
    Public Property Get Created
        Created = m_created
    End Property

    Private Sub Class_Initialize()
        m_dbl_value = 0
        m_created = prom_convert_datetime_utc_to_epoch(prom_get_current_datetime_utc())
    End Sub

    Public Sub inc()
        add(1)
    End Sub

    Public Sub add(dbl_increment)
        If dbl_increment < 0 Then
            Err.Raise 5, "prom_CounterChild.add", "Increment value must be a positive number"
        End If
        m_dbl_value = m_dbl_value + dbl_increment
    End Sub
End Class

%>