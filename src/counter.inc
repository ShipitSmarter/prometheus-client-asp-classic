<!-- #include virtual = "/prometheus-client/collector.inc" -->
<!-- #include virtual = "/prometheus-client/internal/datetime.inc" -->

<%

' Counter metric collector
Class Counter
    Private e_collector

    Public Function Init(p_builder)
        Set e_collector = New Collector.Init(p_builder)
        Set Init = me
    End Function

    Public Function getForLabels(p_labelValues)
        Dim result
        Set result = e_collector.getForLabels(p_labelValues)
        If result Is Nothing Then
            Set result = newChild(p_labelValues)
        End If

        Set getForLabels = result
    End Function

    Public Function getWithoutLabels()
        Set getWithoutLabels = getForLabels(Array())
    End Function

    Public Function collect()
        Dim i, fullname, samples()
        ReDim samples(e_collector.m_children.Count - 1)
        fullname = e_collector.m_name & "_total"
        For i = 0 To e_collector.m_children.Count - 1
            Dim labelValues: labelValues = e_collector.m_children(i).Key
            Dim child: Set child = e_collector.m_children(i).Value
            Set samples(i) = New Sample.Init(fullname, e_collector.m_labelNames, labelValues, child.Value)
        Next
        Set collect = New MetricFamilySamples.Init(MetricType_COUNTER, fullname, e_collector.m_help, samples)
    End Function

    Private Function newChild(p_labels)
        Dim child
        Set child = New CounterChild
        e_collector.addChild child, p_labels
        Set newChild = child
    End Function
End Class

' Builder pattern for Counter
Class CounterBuilder
    Private e_collectionBuilder
    Public Default Property Get ExtendedBuilder ' Extending CollectorBuilder
        Set ExtendedBuilder = e_collectionBuilder
    End Property

    Private Sub Class_Initialize()
        Set e_collectionBuilder = New CollectorBuilder
    End Sub

    ' Create and register the collector with the given registry.
    Public Function register(p_registry)
        Dim counter
        Set counter = New Counter.Init(me)
        p_registry.register(counter)
        Set register = counter
    End Function
End Class

' The value of a single Counter.
Class CounterChild
    Private m_value
    Public Property Get Value()
        Value = m_value
    End Property
    
    ' The datetime when the counter was created, in seconds since epoch
    Private m_created
    Public Property Get Created()
        Created = m_created
    End Property

    Private Sub Class_Initialize()
        m_value = 0
        m_created = convertUtcDateTimeToEpoch(getCurrentDateTimeUtc())
    End Sub

    Public Sub inc()
        incByValue(1)
    End Sub

    Public Sub incByValue(p_increment)
        If p_increment < 0 Then
            Err.Raise 5, "CounterSample.incByValue", "Increment value must be a positive number"
        End If
        m_value = m_value + p_increment
    End Sub
End Class

%>