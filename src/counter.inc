<!-- #include virtual = "/prometheus-client/collector.inc" -->
<!-- #include virtual = "/prometheus-client/internal/datetime.inc" -->

<%

' Counter metric collector
Class Counter
    Private e_collector
    Public Default Property Get ExtendedCollector ' Extending Collector
        Set ExtendedCollector = e_collector
    End Property

    Public Function Init(p_builder)
        Set e_collector = New Collector.Init(p_builder)
        Set Init = me
    End Function

    Public Function getByLabels(p_labelValues)
        Dim result
        Set result = e_collector.getByLabels(p_labelValues)
        If result Is Nothing Then
            Set result = New CounterSample
            result().m_labelValues = p_labelValues
            e_collector.addSample(result)
        End If

        Set getByLabels = result
    End Function

    Public Function getWithoutLabels()
        Dim result
        Set result = e_collector.getWithoutLabels()
        If result Is Nothing Then
            Set result = New CounterSample
            e_collector.addSample(result)
        End if

        Set getWithoutLabels = result
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

' A sample that contains the actual counter metric
Class CounterSample
    Private e_sample
    Public Default Property Get ExtendedSample ' Extending Sample
        Set ExtendedSample = e_sample
    End Property

    Private m_value
    Public Property Get Value()
        Value = m_value
    End Property
    
    ' The datetime when the counter was created, in milliseconds since epoch
    Private m_created
    Public Property Get Created()
        Created = m_created
    End Property

    Private Sub Class_Initialize()
        Set e_sample = New Sample
        m_value = 0
        m_created = convertUtcDateTimeToEpoch(getCurrentDateTimeUtc()) * 1000
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