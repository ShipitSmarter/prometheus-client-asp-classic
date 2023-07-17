<% Option Explicit %>

<!-- #include virtual = "/prometheus-client/collector-registry.inc" -->
<!-- #include virtual = "/prometheus-client/counter.inc" -->
<!-- #include virtual = "/prometheus-client/bridges/prom-exp-fmt.inc" -->

<%

Dim registry
Set registry = New prom_CollectorRegistry
registry.Prefix = "asp_"

Function new_counter(name, help)
    Dim builder
    Set builder = New prom_CounterBuilder
    builder().with_name(name).with_help(help)
    Set new_counter = builder.register(registry)
End Function

Function new_Labeled_counter(name, help, labels)
    Dim builder
    Set builder = New prom_CounterBuilder
    builder().with_name(name).with_help(help).with_label_names(labels)
    Set new_labeled_counter = builder.register(registry)
End Function

Dim some_labeled_counter
Set some_labeled_counter = new_labeled_counter("some_name", "Description of some_name", Array("method", "post"))

Dim another_labeled_counter
Set another_labeled_counter = new_labeled_counter("another_name", "Description of another_name", Array("customer", "user", "location"))

Dim test_labeled_counter_sample
Set test_labeled_counter_sample = some_labeled_counter.get_for_labels(Array("post", "200"))
test_labeled_counter_sample.inc
test_labeled_counter_sample.add 3.254

Dim minimalistic_counter
Set minimalistic_counter = new_counter("without_labels", "Description of without_labels")

' Create some extra samples for testing purposes
some_labeled_counter.get_for_labels(Array("get", "200"))
some_labeled_counter.get_for_labels(Array("post", "500"))
another_labeled_counter.get_for_labels(Array("20", "267", "2367"))
minimalistic_counter.get_without_labels()

prom_write_prom_exp_fmt(registry)

%>