<!-- #include virtual = "/prometheus-client/collector.inc" -->
<%

' Counter metric collector
Class Counter
    Private e_collector
    Public Default Property Get Collector ' Extending Collector
        Set Collector = e_collector
    End Property

    Public Function Init(p_builder)
        Set e_collector = New Collector.Init(p_builder)
        Set Init = me
    End Function
End Class

' Builder pattern for Counter
Class CounterBuilder
    Private e_collectionBuilder
    Public Default Property Get Builder ' Extending CollectorBuilder
        Set Builder = e_collectionBuilder
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

%>