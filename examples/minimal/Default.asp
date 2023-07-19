<%
    Response.CodePage = 65001
    Response.Charset = "utf-8"
    Response.ContentType = "text/plain; version=0.0.4"

    Dim factory: Set factory = Server.CreateObject("SIS.PrometheusCOM.MetricFactory")
    Dim counter: Set counter = factory.CreateCounter("name", "help")
    counter.Inc()

    Dim labeledCounter: Set labeledCounter = factory.CreateLabeledCounter("name2", "help2", Array("label"))
    Dim labeledCounterSample: Set labeledCounterSample = labeledCounter.WithLabels(Array("value"))
    labeledCounterSample.Inc()
    
    Dim registry: Set registry = Server.CreateObject("SIS.PrometheusCOM.CollectorRegistry")
    Response.Write registry.CollectAndExportAsText()
%>