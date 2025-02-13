package com.derailleur.wireless_config

import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.ComponentName
import android.content.ServiceConnection
import android.os.IBinder
import android.util.Log
import androidx.recyclerview.widget.RecyclerView
import android.view.LayoutInflater
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import com.derailleur.wireless_config.databinding.FragmentItemBinding
import java.io.IOException
import java.util.UUID


/**
 * [RecyclerView.Adapter] that can display a [PlaceholderItem].
 * TODO: Replace the implementation with code for your data type.
 */
data class BluetoothDeviceItem(val name: String, val address: String)
class MyDeviceRecyclerViewAdapter(
    private val values: List<BluetoothDeviceItem>
) : RecyclerView.Adapter<MyDeviceRecyclerViewAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {

        return ViewHolder(
            FragmentItemBinding.inflate(
                LayoutInflater.from(parent.context), parent, false
            )
        )

    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val item = values[position]
//        holder.address.text = item.address
        holder.name.text = item.name
        holder.connect_btn.setOnClickListener {
//            connectToBluetoothDevice(item.address)
        }
    }

    override fun getItemCount(): Int = values.size

    inner class ViewHolder(binding: FragmentItemBinding) : RecyclerView.ViewHolder(binding.root) {
        val name: TextView = binding.deviceName
        val address: TextView = binding.deviceAddress
        val connect_btn: Button = binding.connect

        override fun toString(): String {
            return super.toString() + " '" + name.text + "'"
        }
    }






    private var bluetoothService : BluetoothLeService? = null




//    fun connectToBluetoothDevice(address: String) {
//        val bluetoothAdapter: BluetoothAdapter? = BluetoothAdapter.getDefaultAdapter()
//        if (bluetoothAdapter == null) {
//            // Device doesn't support Bluetooth
//            return
//        }
//
//        val device: BluetoothDevice? = bluetoothAdapter.getRemoteDevice(address)
//        if (device == null) {
//            // Device not found
//            return
//        }
//        val uuid: UUID =
//            UUID.fromString("00001101-0000-1000-8000-00805F9B34FB") // Standard SerialPortService ID
//        var socket: BluetoothSocket? = null
//        try {
//            socket = device.createRfcommSocketToServiceRecord(uuid)
//            bluetoothAdapter.cancelDiscovery() //Cancel discovery as it slows down the connection
//            socket.connect()
//            // Connection successful, do something with the socket
//            println("Connected to device: ${device.name}")
//        } catch (e: IOException) {
//            // Connection failed
//            println("Connection failed: ${e.message}")
//            try {
//                socket?.close()
//            } catch (closeException: IOException) {
//                println("Socket close failed: ${closeException.message}")
//            }
//        }
//    }

}

