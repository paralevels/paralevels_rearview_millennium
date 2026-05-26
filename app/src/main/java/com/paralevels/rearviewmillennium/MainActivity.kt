package com.paralevels.rearviewmillennium

import android.app.Activity
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.graphics.Typeface
import android.util.TypedValue
import android.view.Gravity
import android.widget.*
import java.io.File

class MainActivity : Activity() {
    external fun genscene(baseDir: String, choice: Int): String

    companion object {
        init { System.loadLibrary("genscene") }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        installAssetsOnce()

        val splash = TextView(this).apply {
            text = "Rearview Millennium\nParalevels LLC"
            gravity = Gravity.CENTER
            setTextSize(TypedValue.COMPLEX_UNIT_PT, 24f)
            typeface = Typeface.create("sans-serif", Typeface.NORMAL)
        }

        setContentView(splash)

        Handler(Looper.getMainLooper()).postDelayed({
            showScene(0)
        }, 900)
    }

    private fun installAssetsOnce() {
        val marker = File(filesDir, ".installed")
        if (marker.exists()) return

        assets.open("curr").use { input ->
            File(filesDir, "curr").outputStream().use { output -> input.copyTo(output) }
        }

        val scenesDir = File(filesDir, "scenes")
        scenesDir.mkdirs()

        assets.list("scenes")?.forEach { name ->
            assets.open("scenes/$name").use { input ->
                File(scenesDir, name).outputStream().use { output -> input.copyTo(output) }
            }
        }

        marker.writeText("1")
    }

    private fun showScene(choice: Int) {
        val output = genscene(filesDir.absolutePath, choice)
        val lines = output.lines()

        val ascii = lines.take(64).joinToString("\n")
        val caption = lines.getOrNull(65).orEmpty()
        val leftText = lines.getOrNull(67).orEmpty()
        val rightText = lines.getOrNull(69).orEmpty()

        val root = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            setPadding(16, 16, 16, 16)
        }

        val asciiView = TextView(this).apply {
            text = ascii
            typeface = Typeface.MONOSPACE
            setTextSize(TypedValue.COMPLEX_UNIT_PT, 7f)
            includeFontPadding = false
            setLineSpacing(0f, 1.0f)
            gravity = Gravity.CENTER
        }

        val captionView = TextView(this).apply {
            text = caption
            typeface = Typeface.create("sans-serif", Typeface.NORMAL)
            setTextSize(TypedValue.COMPLEX_UNIT_PT, 14f)
            gravity = Gravity.CENTER
            setPadding(0, 12, 0, 12)
        }

        val buttonRow = LinearLayout(this).apply {
            orientation = LinearLayout.HORIZONTAL
            gravity = Gravity.BOTTOM
        }

        val leftButton = Button(this).apply {
            text = leftText
            setTextSize(TypedValue.COMPLEX_UNIT_PT, 32f)
            setOnClickListener { showScene(0) }
        }

        val spacer = Space(this)

        val rightButton = Button(this).apply {
            text = rightText
            setTextSize(TypedValue.COMPLEX_UNIT_PT, 32f)
            setOnClickListener { showScene(1) }
        }

        root.addView(asciiView, LinearLayout.LayoutParams(-1, 0, 1f))
        root.addView(captionView, LinearLayout.LayoutParams(-1, -2))
        buttonRow.addView(leftButton, LinearLayout.LayoutParams(220, 220))
        buttonRow.addView(spacer, LinearLayout.LayoutParams(0, 1, 1f))
        buttonRow.addView(rightButton, LinearLayout.LayoutParams(220, 220))
        root.addView(buttonRow, LinearLayout.LayoutParams(-1, -2))

        setContentView(root)
    }
}
