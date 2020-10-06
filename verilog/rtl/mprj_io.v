module mprj_io(
    inout vdd3v3,
    inout vdd1v8,
    inout vss,
    input vddio_q,
    input vssio_q,
    input analog_a,
    input analog_b,
    input porb_h,
    input por,
    inout [`MPRJ_IO_PADS-1:0] io,
    input [`MPRJ_IO_PADS-1:0] io_out,
    input [`MPRJ_IO_PADS-1:0] oeb,
    input [`MPRJ_IO_PADS-1:0] hldh_n,
    input [`MPRJ_IO_PADS-1:0] enh,
    input [`MPRJ_IO_PADS-1:0] inp_dis,
    input [`MPRJ_IO_PADS-1:0] ib_mode_sel,
    input [`MPRJ_IO_PADS-1:0] vtrip_sel,
    input [`MPRJ_IO_PADS-1:0] slow_sel,
    input [`MPRJ_IO_PADS-1:0] holdover,
    input [`MPRJ_IO_PADS-1:0] analog_en,
    input [`MPRJ_IO_PADS-1:0] analog_sel,
    input [`MPRJ_IO_PADS-1:0] analog_pol,
    input [`MPRJ_IO_PADS*3-1:0] dm,
    output [`MPRJ_IO_PADS-1:0] io_in
);
    `MPRJ_IO_PAD_V(io, io_in, io_out, `MPRJ_IO_PADS, 
    		oeb, hldh_n, enh, inp_dis, ib_mode_sel,
    		vtrip_sel, slow_sel, holdover,
    		analog_en, analog_sel, analog_pol, dm);

endmodule