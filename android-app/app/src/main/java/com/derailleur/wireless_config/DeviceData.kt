package com.derailleur.wireless_config

//class DeviceData {
//}
import android.bluetooth.BluetoothDevice

data class BluetoothDeviceData(
    val device: BluetoothDevice,
    var isConnected: Boolean = false
)