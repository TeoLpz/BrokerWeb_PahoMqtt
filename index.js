  //-------------------------------------ENCENDER LED------------------------------------//
function onLed() {
    const clienteMQTT = new Paho.MQTT.Client('broker.emqx.io', 8084, 'cliente-1');

clienteMQTT.connect({
  onSuccess: function () {
    console.log('LED ENCENDIDO');

    const mensaje = new Paho.MQTT.Message('1');
    mensaje.destinationName = 'UTP';

    clienteMQTT.send(mensaje);
  },
  userName: 'emqx_test',
  password: 'emqx_test',
  useSSL: true,
});
  }

  //-------------------------------------APAGAR LED------------------------------------//
  function offLed() {
    const clienteMQTT = new Paho.MQTT.Client('broker.emqx.io', 8084, 'cliente-1');

clienteMQTT.connect({
  onSuccess: function () {
    console.log('LED APAGADO');

    const mensaje = new Paho.MQTT.Message('0');
    mensaje.destinationName = 'UTP';

    clienteMQTT.send(mensaje);
  },
  userName: 'emqx_test',
  password: 'emqx_test',
  useSSL: true,
});
  }