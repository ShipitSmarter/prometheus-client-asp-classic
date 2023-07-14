<%

' A metric and all of its samples.
Class MetricFamilySamples
    Private m_type
    Public Property Get MetricType
        MetricType = m_type
    End Property

    Private m_name
    Public Property Get Name
        Name = m_name
    End Property

    Private m_help
    Public Property Get Help
        Help = m_help
    End Property

    Private m_samples
    Public Property Get Samples
        Samples = m_samples
    End Property

    Public Function Init(p_type, p_name, p_help, p_samples)
        m_type = p_type
        m_name = p_name
        m_help = p_help
        m_samples = p_samples
        Set Init = me
    End Function
End Class

' A single sample with a unique name and set of labels
Class Sample
    Private m_name
    Public Property Get Name
        Name = m_name
    End Property

    Private m_labelNames
    Public Property Get LabelNames
        LabelNames = m_labelNames
    End Property
    
    Private m_labelValues
    Public Property Get LabelValues
        LabelValues = m_labelValues
    End Property

    Private m_value
    Public Property Get Value
        Value = m_value
    End Property

    Private m_created
    Public Property Get Created
        Created = m_created
    End Property

    Public Function Init(p_name, p_labelNames, p_labelValues, p_value, p_created)
        m_name = p_name
        m_labelNames = p_labelNames
        m_labelValues = p_labelValues
        m_value = p_value
        m_created = p_created
        Set Init = me
    End Function
End Class

' MetricType Enum
Const MetricType_COUNTER = 1
Const MetricType_GAUGE = 2

%>