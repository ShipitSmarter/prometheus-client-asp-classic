<%
    Response.CodePage = 65001
    Response.Charset = "utf-8"
    Response.ContentType = "text/plain; version=0.0.4"

    Dim metrics: Set metrics = Server.CreateObject("SIS.PrometheusCOM.Metrics")
    Dim counter: Set counter = metrics.CreateCounter("name", "help")
    counter.Inc()

    Dim labeledCounter: Set labeledCounter = metrics.CreateLabeledCounter("name2", "help2", Array("label"))
    Dim labeledCounterSample: Set labeledCounterSample = labeledCounter.WithLabels(Array("value"))
    labeledCounterSample.Inc()

    Response.Write metrics.Registry.CollectAndExportAsText()
%>