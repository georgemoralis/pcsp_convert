/*
Parts based on soywiz's pspemulator.

This file is part of jpcsp.

Jpcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Jpcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Jpcsp.  If not, see <http://www.gnu.org/licenses/>.
 */
package jpcsp.graphics;

import java.util.Iterator;
import javax.media.opengl.GL;
import jpcsp.Emulator;
import static jpcsp.graphics.GeCommands.*;

public class VideoEngine {

    private static VideoEngine instance;
    private GL gl;

    private boolean fullscreen;
    private int mode;
    private int linesize;
    private int pixelsize;
    private int width;
    private int height;
    private boolean ha;
    private static final boolean isDebugMode = true;
    private static GeCommands helper;
    private VertexInfo vinfo = new VertexInfo();
    private static final char SPACE = ' ';

    // TODO these currently here for testing only
    private int fbp, fbw; // frame buffer pointer and width
    private int zbp, zbw; // depth buffer pointer and width
    private int psm; // pixel format

    private boolean proj_upload_start;
    private int proj_upload_x;
    private int proj_upload_y;
    private float[] proj_matrix = new float[4 * 4];


    private boolean world_upload_start;
    private int world_upload_x;
    private int world_upload_y;
    private float[] world_matrix = new float[4 * 4];

    private boolean listIsOver;
    private DisplayList actualList; // The currently executing list
    private int clearFlags;
    private static void log(String msg) {
        if (isDebugMode) {
            System.out.println("sceGe DEBUG > " + msg);
        }
    }

    public static VideoEngine getEngine(GL gl, boolean fullScreen, boolean hardwareAccelerate) {
        VideoEngine engine = getEngine();
        engine.setFullScreenShoot(fullScreen);
        engine.setHardwareAcc(hardwareAccelerate);
        engine.gl = gl;
        return engine;
    }

    private static VideoEngine getEngine() {
        if (instance == null) {
            instance = new VideoEngine();
            helper = new GeCommands();
        }
        return instance;
    }

    private VideoEngine() {
    }

    // call from GL thread
    public void update() {
        //System.err.println("update start");
        DisplayList.Lock();
        Iterator<DisplayList> it = DisplayList.iterator();
        while(it.hasNext() && !Emulator.pause) {
            DisplayList list = it.next();
            if (list.status == DisplayList.QUEUED) {
                //System.err.println("executeList");
                executeList(list);

                if (list.status == DisplayList.DONE)
                    it.remove();
            }
        }
        DisplayList.Unlock();
        //System.err.println("update done");
    }

    // call from GL thread
    private void executeList(DisplayList list) {
        actualList = list;
        listIsOver = false;

        log("executeList id " + list.id);

        while (!listIsOver &&
            actualList.pc != actualList.stallAddress &&
            !Emulator.pause) {
            int ins = Emulator.getMemory().read32(actualList.pc);
            actualList.pc += 4;
            executeCommand(ins);
        }

        if (actualList.pc == actualList.stallAddress) {
            actualList.status = DisplayList.STALL_REACHED;
            log("list " + actualList.id + " stalled at " + String.format("%08x", actualList.stallAddress));
        }

        if (listIsOver) {
            // Set list for deferred remove
            actualList.status = DisplayList.DONE;
            actualList = null;
        }
    }

    //I guess here we use ubyte
    private int command(int instruction) {
        return (instruction >>> 24);
    }

    private int intArgument(int instruction) {
        return (instruction & 0x00FFFFFF);
    }

    private float floatArgument(int instruction) {
        return Float.intBitsToFloat(instruction << 8);
    }

    public void executeCommand(int instruction) {
        int normalArgument = intArgument(instruction);
        float floatArgument = floatArgument(instruction);

        switch (command(instruction)) {
            case END:
                listIsOver = true;
                log(helper.getCommandString(END));
                break;
            case FINISH:
                listIsOver = true;
                log(helper.getCommandString(FINISH));
                break;
            case BASE:
                actualList.base = normalArgument << 8;
                log(helper.getCommandString(BASE) + " " + String.format("%08x", actualList.base));
                break;
            case IADDR:
                vinfo.ptr_index = actualList.base | normalArgument;
                log(helper.getCommandString(IADDR) + " " + String.format("%08x", vinfo.ptr_index));
                break;
            case VADDR:
                vinfo.ptr_vertex = actualList.base | normalArgument;
                log(helper.getCommandString(VADDR) + " " + String.format("%08x", vinfo.ptr_vertex));
                break;
            case VTYPE:
                vinfo.processType(normalArgument);
                log(helper.getCommandString(VTYPE) + " " + vinfo.toString());
                break;

            case TME:
                if (normalArgument != 0) {
                    gl.glEnable(GL.GL_TEXTURE_2D);
                    log("sceGuEnable(GU_TEXTURE_2D)");
                } else {
                    gl.glDisable(GL.GL_TEXTURE_2D);
                    log("sceGuDisable(GU_TEXTURE_2D)");
                }
                break;

            case WMS:
                // TODO figure out how to handle the separate MODEL and VIEW/WORLD matrix stacks
                gl.glMatrixMode(GL.GL_MODELVIEW);
                world_upload_start = true;
                log("sceGumMatrixMode GU_MODEL");
                break;

            case WORLD:
                if (world_upload_start) {
                    world_upload_x = 0;
                    world_upload_y = 0;
                    world_upload_start = false;
                }

                if (world_upload_y < 4) {
                    if (world_upload_x < 3) {
                        world_matrix[world_upload_x + world_upload_y * 4] = floatArgument;

                        world_upload_x++;
                        if (world_upload_x == 3) {
                            world_matrix[world_upload_x + world_upload_y * 4] = (world_upload_y == 3) ? 1.0f : 0.0f;
                            world_upload_x = 0;
                            world_upload_y++;
                            if (world_upload_y == 4) {
                                log("glLoadMatrixf", world_matrix);
                                gl.glLoadMatrixf(world_matrix, 0);
                            }
                        }
                    }
                }
                break;

            case PMS:
                gl.glMatrixMode(GL.GL_PROJECTION);
                proj_upload_start = true;
                log("sceGumMatrixMode GU_PROJECTION");
                break;

            case PROJ:
                if (proj_upload_start) {
                    proj_upload_x = 0;
                    proj_upload_y = 0;
                    proj_upload_start = false;
                }

                if (proj_upload_y < 4) {
                    if (proj_upload_x < 4) {
                        proj_matrix[proj_upload_x + proj_upload_y * 4] = floatArgument;

                        proj_upload_x++;
                        if (proj_upload_x == 4) {
                            proj_upload_x = 0;
                            proj_upload_y++;
                            if (proj_upload_y == 4) {
                                log("glLoadMatrixf", proj_matrix);
                                gl.glLoadMatrixf(proj_matrix, 0);
                            }
                        }
                    }
                }
                break;

            case XSCALE:
                log("sceGuViewport width = " + (floatArgument * 2));
                break;
            case YSCALE:
                log("sceGuViewport height = " + (- floatArgument * 2));
                break;

            // sceGuViewport cx/cy, can we discard these settings? it's only for clipping?
            case XPOS:
                log("sceGuViewport cx = " + floatArgument);
                break;
            case YPOS:
                log("sceGuViewport cy = " + floatArgument);
                break;

            case ZPOS:
                log(helper.getCommandString(ZPOS), floatArgument);
                break;
            // sceGuOffset, can we discard these settings? it's only for clipping?
            case OFFSETX:
                log("sceGuOffset x = " + (normalArgument >> 4));
                break;
            case OFFSETY:
                log("sceGuOffset y = " + (normalArgument >> 4));
                break;

            case FBP:
                // assign or OR lower 24-bits?
                fbp = normalArgument;
                break;
            case FBW:
                fbp &= 0xffffff;
                fbp |= (normalArgument << 8) & 0xff000000;
                fbw = (normalArgument) & 0xffff;
                log("fbp=" + Integer.toHexString(fbp) + ", fbw=" + fbw);
                break;

            case ZBP:
                // assign or OR lower 24-bits?
                zbp = normalArgument;
                break;
            case ZBW:
                zbp &= 0xffffff;
                zbp |= (normalArgument << 8) & 0xff000000;
                zbw = (normalArgument) & 0xffff;
                log("zbp=" + Integer.toHexString(zbp) + ", zbw=" + zbw);
                break;

            case PSM:
                psm = normalArgument;
                log("psm=" + normalArgument);
                break;

            case PRIM:
            {
                int[] mapping = new int[] { GL.GL_POINTS, GL.GL_LINES, GL.GL_LINE_STRIP, GL.GL_TRIANGLES, GL.GL_TRIANGLE_STRIP, GL.GL_TRIANGLE_FAN };
                int numberOfVertex = normalArgument & 0xFFFF;
                int type = ((normalArgument >> 16) & 0x7);

                // Logging
                switch (type) {
                    case PRIM_POINT:
                        log(helper.getCommandString(PRIM) + " point");
                        break;
                    case PRIM_LINE:
                        log(helper.getCommandString(PRIM) + " line");
                        break;
                    case PRIM_LINES_STRIPS:
                        log(helper.getCommandString(PRIM) + " lines_strips");
                        break;
                    case PRIM_TRIANGLE:
                        log(helper.getCommandString(PRIM) + " triangle");
                        break;
                    case PRIM_TRIANGLE_STRIPS:
                        log(helper.getCommandString(PRIM) + " triangle_strips");
                        break;
                    case PRIM_TRIANGLE_FANS:
                        log(helper.getCommandString(PRIM) + " triangle_fans");
                        break;
                    case PRIM_SPRITES:
                        log(helper.getCommandString(PRIM) + " sprites");
                        break;
                }

                // GL
                switch (type) {
                    case PRIM_POINT:
                    case PRIM_LINE:
                    case PRIM_LINES_STRIPS:
                    case PRIM_TRIANGLE:
                    case PRIM_TRIANGLE_STRIPS:
                    case PRIM_TRIANGLE_FANS:
                        gl.glBegin(mapping[type]);
                            for (int i = 0; i < numberOfVertex; i++) {
                                int addr = vinfo.getAddress(i);
                                VertexState v = vinfo.readVertex(Emulator.getMemory(), addr);
                                if (vinfo.texture  != 0) gl.glTexCoord2f(v.u, v.v);
                                if (vinfo.color    != 0) gl.glColor4f(v.r, v.g, v.b, v.a);
                                if (vinfo.normal   != 0) gl.glNormal3f(v.nx, v.ny, v.nz);
                                if (vinfo.position != 0) gl.glVertex3f(v.px, v.py, v.pz);
                            }
                        gl.glEnd();
                        break;

                    case PRIM_SPRITES:
                        gl.glPushAttrib(GL.GL_CULL_FACE);
                        gl.glDisable(GL.GL_CULL_FACE);
                        gl.glBegin(GL.GL_QUADS);
                            for (int i = 0; i < numberOfVertex; i += 2) {
                                int addr1 = vinfo.getAddress(i);
                                int addr2 = vinfo.getAddress(i + 1);
                                VertexState v1 = vinfo.readVertex(Emulator.getMemory(), addr1);
                                VertexState v2 = vinfo.readVertex(Emulator.getMemory(), addr2);

                                // V1
                                if (vinfo.normal   != 0) gl.glNormal3f(v1.nx, v1.ny, v1.nz);
                                if (vinfo.color    != 0) gl.glColor4f(v1.r, v1.g, v1.b, v1.a);

                                if (vinfo.texture  != 0) gl.glTexCoord2f(v1.u, v1.v);
                                if (vinfo.position != 0) gl.glVertex3f(v1.px, v1.py, v1.pz);

                                if (vinfo.texture  != 0) gl.glTexCoord2f(v2.u, v1.v);
                                if (vinfo.position != 0) gl.glVertex3f(v2.px, v1.py, v1.pz);

                                // V2
                                if (vinfo.normal   != 0) gl.glNormal3f(v2.nx, v2.ny, v2.nz);
                                if (vinfo.color    != 0) gl.glColor4f(v2.r, v2.g, v2.b, v2.a);

                                if (vinfo.texture  != 0) gl.glTexCoord2f(v2.u, v2.v);
                                if (vinfo.position != 0) gl.glVertex3f(v2.px, v2.py, v1.pz);

                                if (vinfo.texture  != 0) gl.glTexCoord2f(v1.u, v2.v);
                                if (vinfo.position != 0) gl.glVertex3f(v1.px, v2.py, v1.pz);

                            }
                        gl.glEnd();
                        gl.glPopAttrib();
                        break;
                }
                break;
            }

            case SHADE:
            {
                int SETTED_MODEL = (normalArgument != 0) ? GL.GL_SMOOTH : GL.GL_FLAT;
                gl.glShadeModel(SETTED_MODEL);
                log(helper.getCommandString(SHADE) + " " + ((normalArgument != 0) ? "smooth" : "flat"));
                break;
            }

            case FFACE:
            {
                int frontFace = (normalArgument != 0) ? GL.GL_CW : GL.GL_CCW;
                gl.glFrontFace(frontFace);
                log(helper.getCommandString(FFACE) + " " + ((normalArgument != 0) ? "clockwise" : "counter-clockwise"));
                break;
            }
            case BCE:
                if(normalArgument != 0)
                {
                    gl.glEnable(GL.GL_CULL_FACE);
                    log("sceGuEnable(GU_CULL_FACE)");
                }
                else
                {
                    gl.glDisable(GL.GL_CULL_FACE);
                    log("sceGuDisable(GU_CULL_FACE)");
                }    
                break;
            case FGE:
                if(normalArgument != 0)
                {
                    gl.glEnable(GL.GL_FOG);
                    gl.glFogi(GL.GL_FOG_MODE, GL.GL_LINEAR);
		    gl.glFogf(GL.GL_FOG_DENSITY, 0.1f);
		    gl.glHint(GL.GL_FOG_HINT, GL.GL_DONT_CARE);
                    log("sceGuEnable(GL_FOG)");
                }
                else
                {
                    gl.glDisable(GL.GL_FOG);
                    log("sceGuDisable(GL_FOG)");
                } 
                break;
            case ABE:
                if(normalArgument != 0)
                {
                    gl.glEnable(GL.GL_BLEND);
                    log("sceGuEnable(GU_BLEND)");
                }
                else
                {
                    gl.glDisable(GL.GL_BLEND);
                    log("sceGuDisable(GU_BLEND)");
                }    
                break;
            case ZTE:
                if(normalArgument != 0)
                {
                    gl.glEnable(GL.GL_DEPTH_TEST);
                    log("sceGuEnable(GU_DEPTH_TEST)");
                }
                else
                {
                    gl.glDisable(GL.GL_DEPTH_TEST);
                    log("sceGuDisable(GU_DEPTH_TEST)");
                }    
                break;
            case STE:
                if(normalArgument != 0)
                {
                    gl.glEnable(GL.GL_STENCIL_TEST);
                    log("sceGuEnable(GU_STENCIL_TEST)");
                }
                else
                {
                    gl.glDisable(GL.GL_STENCIL_TEST);
                    log("sceGuDisable(GU_STENCIL_TEST)");
                }    
                break;
            case LOE:
                if(normalArgument != 0)
                {
                    gl.glEnable(GL.GL_COLOR_LOGIC_OP);
                    log("sceGuEnable(GU_COLOR_LOGIC_OP)");
                }
                else
                {
                    gl.glDisable(GL.GL_COLOR_LOGIC_OP);
                    log("sceGuDisable(GU_COLOR_LOGIC_OP)");
                }    
                break;
            case JUMP:
                int npc = (normalArgument | actualList.base) & 0xFFFFFFFC;
                //I guess it must be unsign as psp player emulator
                log(helper.getCommandString(JUMP) + " old PC:" + String.format("%08x", actualList.pc)
                    + " new PC:" + String.format("%08x", npc));
                actualList.pc = npc;
                break;
            case CALL:
                actualList.stack[actualList.stackIndex++] = actualList.pc + 4;
                actualList.pc = (normalArgument | actualList.base) & 0xFFFFFFFC;
                log(helper.getCommandString(CALL), actualList.pc);
                break;
            case RET:
                actualList.pc = actualList.stack[--actualList.stackIndex];
                log(helper.getCommandString(RET), actualList.pc);
                break;
            case CLEAR:
                if ((normalArgument & 0x1)==0) {
			gl.glClear(clearFlags);
                        log("guclear");
		} else {
		     clearFlags = 0;
		     if ((normalArgument & 0x100)!=0) clearFlags |= GL.GL_COLOR_BUFFER_BIT; // target
		     if ((normalArgument & 0x200)!=0) clearFlags |= GL.GL_ACCUM_BUFFER_BIT | GL.GL_STENCIL_BUFFER_BIT; // stencil/alpha
		     if ((normalArgument & 0x400)!=0) clearFlags |= GL.GL_DEPTH_BUFFER_BIT; // zbuffer
		     log("setting clear flags");
                }
                break;
            case NOP:
                log(helper.getCommandString(NOP));
                break;

            default:
                log("Unknown/unimplemented video command [ " + helper.getCommandString(command(instruction)) + " ]");
        }

    }

    public void setFullScreenShoot(boolean b) {
    }

    public void setLineSize(int linesize) {
    }

    public void setMode(int mode) {
    }

    public void setPixelSize(int pixelsize) {
    }

    public void setup(int mode, int xres, int yres) {
    }

    public void show() {
    }

    public void waitVBlank() {
    }

    private void log(String commandString, float floatArgument) {
        log(commandString+SPACE+floatArgument);
    }

    private void log(String commandString, int value) {
        log(commandString+SPACE+value);
    }

    private void log(String commandString, float[] matrix) {
        for (int y = 0; y < 4; y++) {
            log(commandString+SPACE+String.format("%.1f %.1f %.1f %.1f", matrix[0 + y * 4], matrix[1 + y * 4], matrix[2 + y * 4], matrix[3 + y * 4]));
        }
    }

    private void setHardwareAcc(boolean hardwareAccelerate) {
    }
}
