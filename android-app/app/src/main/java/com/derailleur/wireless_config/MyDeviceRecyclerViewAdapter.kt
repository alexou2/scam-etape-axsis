package com.derailleur.wireless_config

import androidx.recyclerview.widget.RecyclerView
import android.view.LayoutInflater
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import com.derailleur.wireless_config.databinding.FragmentItemBinding


/**
 * [RecyclerView.Adapter] that can display a [PlaceholderItem].
 * TODO: Replace the implementation with code for your data type.
 */
data class BluetoothDeviceItem(val name: String, val address: String)
class MyDeviceRecyclerViewAdapter(
        private val values: List<BluetoothDeviceItem>)
    : RecyclerView.Adapter<MyDeviceRecyclerViewAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {

    return ViewHolder(FragmentItemBinding.inflate(LayoutInflater.from(parent.context), parent, false))

    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val item = values[position]
//        holder.address.text = item.address
        holder.name.text = item.name
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

}

