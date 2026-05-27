package com.paralevels.rearviewmillennium

import android.annotation.SuppressLint
import android.app.Activity
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.graphics.Typeface
import android.util.TypedValue
import android.view.Gravity
import android.widget.*
import java.io.File
import android.graphics.Color
import android.view.View

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

    @SuppressLint("SetTextI18n")
    private fun showScene(choice: Int) {
        val output = genscene(filesDir.absolutePath, choice)
        val lines = output.lines()

        val ascii = lines.take(64).joinToString("\n")
        val caption = lines.getOrNull(65).orEmpty()
        val leftText = lines.getOrNull(67).orEmpty()
        val rightText = lines.getOrNull(69).orEmpty()

        val root = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            setPadding(24, 24, 24, 24)
            setBackgroundColor(Color.BLACK)
        }

        val asciiView = TextView(this).apply {
            text = ascii
            typeface = Typeface.MONOSPACE
            setTextSize(TypedValue.COMPLEX_UNIT_PT, 3.7f)
            includeFontPadding = false
            setLineSpacing(0f, 1.0f)
            setTextColor(Color.GREEN)
            gravity = Gravity.CENTER_HORIZONTAL
        }

        val captionView = TextView(this).apply {
            text = caption
            typeface = Typeface.create("sans-serif", Typeface.NORMAL)
            setTextSize(TypedValue.COMPLEX_UNIT_PT, 8f)
            setTextColor(Color.GRAY)
            gravity = Gravity.TOP
            setPadding(8, 8, 8, 8)
        }

        val buttonRow = LinearLayout(this).apply {
            orientation = LinearLayout.HORIZONTAL
            gravity = Gravity.BOTTOM
        }

        val leftButton = Button(this).apply {
            text = leftText
            setTextSize(TypedValue.COMPLEX_UNIT_PT, 10f)
            isAllCaps = false
            setBackgroundColor(Color.GREEN)
            setOnClickListener { showScene(0) }
        }
        // Disable, hide, still holds space
        if (leftText.isEmpty()) {
            leftButton.isEnabled = false
            leftButton.visibility = View.INVISIBLE
        }

        val middleLayout = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            gravity = Gravity.BOTTOM or Gravity.CENTER_HORIZONTAL // Bottom-center
        }

        val exitButton = Button(this).apply {
            text = "EXIT"
            setTextSize(TypedValue.COMPLEX_UNIT_PT, 7f)
            setTextColor(Color.BLUE)
            setBackgroundColor(Color.BLACK)
            gravity = Gravity.CENTER
            setOnClickListener { finish() }
        }

        val rightButton = Button(this).apply {
            text = rightText
            setTextSize(TypedValue.COMPLEX_UNIT_PT, 10f)
            isAllCaps = false
            setBackgroundColor(Color.GREEN)
            setOnClickListener { showScene(1) }
        }
        // Disable, hide, still holds space
        if (rightText.isEmpty()) {
            rightButton.isEnabled = false
            rightButton.visibility = View.INVISIBLE
        }

        // Set linear layout parameters
        val asciiParams = LinearLayout.LayoutParams(-1, -2)
        val captionParams = LinearLayout.LayoutParams(-1, 0, 1f)
        val buttonRowParams = LinearLayout.LayoutParams(-1, -2)
        val leftButtonParams = LinearLayout.LayoutParams(400, 240)
        val middleLayoutParams = LinearLayout.LayoutParams(0, -1, 1f)
        val exitButtonParams = LinearLayout.LayoutParams(120, 100)
        val rightButtonParams = LinearLayout.LayoutParams(400, 240)

        // Set margins
        asciiParams.bottomMargin = 16
        captionParams.topMargin = 8
        captionParams.bottomMargin = 16
        buttonRowParams.bottomMargin = 32

        //Build view tree
        root.addView(asciiView, asciiParams)
        root.addView(captionView, captionParams)
        buttonRow.addView(leftButton, leftButtonParams)
        middleLayout.addView(exitButton, exitButtonParams)
        buttonRow.addView(middleLayout, middleLayoutParams)
        buttonRow.addView(rightButton, rightButtonParams)
        root.addView(buttonRow, buttonRowParams)

        setContentView(root)
    }
}
